#include "stdafx.h"
#include "stdio.h"
#include "Aspi.h"
#include "CDVDMain.h"
#include "ntddscsi.h"

typedef struct _Known
{
	char h,l;
	char *desc;
} Known;

Known Types2[]=
{
	{'X','A',"SD-M 1002"},
	{'X','B',"SD-M 1102"},
	{'X','C',"SD-M 1202"},
	{'X','D',"SD-M 1212/SD-C 2202"},
	{'X','F',"SD-M 1302/SD-C 2302"},
	{'X','G',"SD-M 1402 v1/SD-C 2402"},
	{'X','H',"SD-M 1222"},
	{'X','I',"SD-C 2502"},
	{'X','J',"SD-M 1502 revA/SD-C 2512"},
	{'X','K',"SD-M 1402 revB"},
	{'X','M',"SD-M 1502 revB"},
	{'X','N',"SD-M 1612 revA"},
	{'X','O',"SD-M 1612 revB/SD-C 2612"},
	{'X','P',"SD-M 1612 revC"},
	{'X','Q',"SD-M 1712"},        
	{'Y','D',"SD-M 1201"},
	{'Y','G',"SD-M 1401"},
  	{'Y','F',"SD-M 1301"},
	{'Y','Q',"SD-M 1711"},
	{'H','M',"SD-R 1002"},
	{'H','N',"SD-R 1102"},
	{'H','P',"SD-R 1202/1202F"},
	{'H','Q',"SD-R 1312"},
	{'I','M',"SD-R 2002 revA"},
	{'I','N',"SD-R 2002 revB"},
	{'I','O',"SD-R 2102 revA"},
	{'I','P',"SD-R 2102 revB"},
	{'I','Q',"SD-R 2212 revA"},
	{'I','R',"SD-R 2212 revB"},
	{'I','S',"SD-R 2312"},
	{'I','T',"SD-R 2412"},
	{'K','M',"SD-R 5002"},
	{'K','N',"SD-R 5112"},    
	{'L','M',"SD-R 6012"},
	{'L','O',"SD-R 6112"},
};

Device *devices = NULL;
int deviceCount = 0;
HANDLE event = NULL;

//char LogFileDir[255];
//sprintf(LogFileDir[255],"%s",GetCurrentDir());

bool DumpableDrive(Device* dev)
{
	char* goodDrive[] =
	{
		"TOSHIBA",
		"Toshiba",
		"KiSS",
		"Compaq",
		NULL
	};
        
	for (char** current = &goodDrive[0]; *current; ++current) if (strncmp (dev->name, *current, strlen(*current)) == 0) return true;
	return false;
}

// Make a list of available SCSI devices
DWORD Device::makeDeviceList(void)
{
	unsigned long i;
	char name[16];
	unsigned long len;
	unsigned long bank,offset,Length;
    char fk[20];
   	unsigned char buffer[2048];
	unsigned char b[256];
	unsigned char cmd[12];
	unsigned char cmd2[9];    
   	BYTE CDB[16];
	unsigned char bx[255];
	char flags;
	char resets;
	char changes;
	char *r_mask[1];
    int foundit=0;
    DWORD d,calc;
    int lenData;
    int AdditionalLength, NumberofProfiles;
    BYTE *p;
    BYTE *pMax = b + 256;
    SRB_ExecSCSICmd s;
    BYTE CDComp[20];
   	int adaptorID, targetID, unitID;
   	Inquiry inq;
   	Device *dev;
    DWORD status;
    DWORD dwFlags = GENERIC_READ;

    int iOSVer = getOsVersion();

    if ( iOSVer >= OS_WIN2K )
      dwFlags |= GENERIC_WRITE;

    //FILE* fx = fopen("_data.bin", "wb");

	// Delete the current devices if any are there
	if (devices)
	{
		Device *temp = devices, *p;

		for (; temp; temp = p)
		{
			p = temp->next;
			delete temp;
		}

		devices = NULL;
		deviceCount = 0;
	}

   	// Loop to create list of devices

    // SPTI
    if (Main_Form->SPTI1->Checked)
    {

        #ifdef DISCInfo_DEBUG
            write_log("---------------------------------------------");        
            write_log("Searching for drives in SPTI mode");
        #endif
        
        for (char c='C';c<='Z';c++)
        {
            String S = String(c) + ":";
            if ( GetDriveType( S.c_str() ) == DRIVE_CDROM || GetDriveType( S.c_str() ) == DRIVE_FIXED || GetDriveType( S.c_str() ) == DRIVE_REMOVABLE)
            {

                dev = new Device();

                if (!Main_Form->Displayotherdevices1->Checked)
                {
                    // Is it a CD-ROM?
                    if ((GetDriveType( S.c_str() ) != DRIVE_CDROM))
                    {
                        delete dev;
                        continue;
                    }
                }

                memset((void *) &inq, 0, sizeof(Inquiry));

                //sprintf( dev->letter, "%c", c );
                dev->letter[0] = c;
                dev->letter[1]=0;

        		// Send SCSI command
        		memset((void *) CDB, 0, sizeof(CDB));
                CDB[0] = SCSI_INQUIRY;
                CDB[4] = 56;

                status=dev->SendSPTICommand(CDB, 6, dwFlags, SCSI_IOCTL_DATA_IN,(BYTE *) &inq, sizeof(Inquiry));

                if (status!=0)
                {
                    #ifdef DISCInfo_DEBUG
                        char logz[255];
                        sprintf(logz,"Inquiry doesn't work with drive letter %s:",(AnsiString)dev->letter);
                        write_log(logz);
                    #endif

                    delete dev;
                    // No device is a normal error
                    continue;
                }

                // Not needed for SPTI
        		dev->HaId = 0;
                dev->Target = 0;
                dev->Lun = 0;
                // Not needed for SPTI

        		memcpy(dev->name, inq.Vendor, 49);
        		dev->name[49] = 0;

                memcpy(dev->interfacex, &inq.interfx[1], 1);

                dev->type=inq.devType;

                memcpy(dev->vendor_name, inq.Vendor, 24);
                dev->vendor_name[24] = 0;

                memcpy(dev->firmware_version, &(inq.Vendor[24]), 4);
                dev->firmware_version[4] = 0;

                char extra_string[20];
                strcpy(extra_string, &(inq.Vendor[28]));
                extra_string[20]=0;

                strcpy(dev->extra_info, extra_string);

                char combo_string[50];
                char combo_vendor[25];
                memcpy(combo_vendor, dev->name, 24);
                combo_vendor[24] = 0;

                sprintf(combo_string,"%s: %s",dev->letter,combo_vendor);

                #ifdef DISCInfo_DEBUG
                    char logz[255];
                    sprintf(logz,"Added the drive %s into the combobox",(AnsiString)combo_string);
                    write_log(logz);
                #endif

                Main_Form->ComboBox->Items->Add(combo_string);
                Main_Form->ComboBox->ItemIndex=0;

                deviceCount++;

                dev->next = devices;
                dev->prev = NULL;
                if (devices)
                    devices->prev = dev;
                devices = dev;
            }
        }
    } else
    {
        // ASPI
        status = GetASPI32SupportInfo();
        int tempCount = LOBYTE(status);

        deviceCount = 0;

         // SCSI error occurred?
        if (HIBYTE(LOWORD(status)) != SS_COMP)
        return (DWORD) -1;

        // Are there no adaptors?  This isn't an error condition.
        if (!tempCount)
        return 0;

        for (adaptorID = (tempCount - 1); adaptorID >= 0; adaptorID--)
            for (targetID = (MAX_ID - 1); targetID >= 0; targetID--)
         		for (unitID = (MAX_ID - 1); unitID >= 0; unitID--)
         		{
         			// Create a new Device and initialize it
         			dev = new Device();

         			dev->HaId = adaptorID;
         			dev->Target = targetID;
         			dev->Lun = unitID;
         			memset((void *) &inq, 0, sizeof(Inquiry));

         			// Send SCSI command
         			memset((void *) CDB, 0, sizeof(CDB));
         			CDB[0] = SCSI_INQUIRY;
         			CDB[4] = 56;

         			if (!!(dev->SendCommand(CDB, 6, SRB_DIR_IN,(BYTE *) &inq, sizeof(Inquiry))))
         			{
         				delete dev;
         				// No device is a normal error
         				continue;
         			}

         			memcpy(dev->name, inq.Vendor, 49);
         			dev->name[49] = 0;

         			memcpy(dev->interfacex, &inq.interfx[1], 1);

                    dev->type=inq.devType;

                    if (!Main_Form->Displayotherdevices1->Checked)
                    {
               			// Is it a CD-ROM?
           				if ((inq.devType != DTYPE_CROM) && (inq.devType != DTYPE_WORM))
         	        	{
                 			delete dev;
               				continue;
           				}
                    }

                    if (inq.devType == DTYPE_PROC) // SPECIAL CASE FOR RAID MOBOs
                	{
        	        	delete dev;
        	            continue;
                    }

       				memcpy(dev->vendor_name, inq.Vendor, 24);
       				dev->vendor_name[24] = 0;

       				memcpy(dev->firmware_version, &(inq.Vendor[24]), 4);
       				dev->firmware_version[4] = 0;
                    char extra_string[20];

                    strcpy(extra_string, &(inq.Vendor[28]));
                    extra_string[20]=0;

      				strcpy(dev->extra_info, extra_string);

                    char combo_string[50];
                    char combo_vendor[25];
      				memcpy(combo_vendor, dev->name, 24);
       				combo_vendor[24] = 0;
                    sprintf(combo_string,"%i:%i:%i %s",dev->HaId,dev->Target,dev->Lun,combo_vendor);

                    #ifdef DISCInfo_DEBUG
                        char logz[255];
                        sprintf(logz,"Added the drive %s into the combobox",(AnsiString)combo_string);
                        write_log(logz);
                    #endif

                    Main_Form->ComboBox->Items->Add(combo_string);
                    Main_Form->ComboBox->ItemIndex=0;

     				deviceCount++;

       				dev->next = devices;
       				dev->prev = NULL;
       				if (devices)
       					devices->prev = dev;
       				devices = dev;
                }
    }
    
    for (dev = devices; dev; dev = dev->next)
    {

        #ifdef DISCInfo_DEBUG
            char logz[255];
            sprintf(logz,"*** Started to query %s for info ***",AnsiString(dev->vendor_name).Trim());
            write_log("---------------------------------------------");
            write_log(logz);
        #endif

        dev->if_toshiba=false;
        
        // BEGIN TOSHIBA DUMPING OF TWO BYTE
        if (DumpableDrive (dev))
        {

            #ifdef DISCInfo_DEBUG
                write_log("Drive is Toshiba so let's check for it's firmware code");
            #endif

            // TWO CHAR INFO
            // first write the bank into bank switch register at F003

            p = (char *) cmd;
            *p++ = 0x1D;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x08;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x00;

            p = (char *) buffer;
            *p++ = 0x88;
            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x04;
            *p++ = 0x00;
            *p++ = 0x40;
            *p++ = 0x00;
            *p++ = 0x00;

            if (Main_Form->SPTI1->Checked)
            {
                status = dev->SendSPTICommand(cmd, 12, dwFlags, SCSI_IOCTL_DATA_OUT, (unsigned char *) buffer, 0x0A);
            }
            else
            {
                status = dev->SendCommand(cmd, 12, SRB_DIR_OUT, (unsigned char *) buffer, 0x0A);
            }

            if (status != 0)
            {
                #ifdef DISCInfo_DEBUG
                    write_log("First Toshiba command failed");
                #endif
                dev->if_toshiba=false;
                dev->fw_code[0]=0;
                dev->tosh_model[0]=0;
            } else
            {
                #ifdef DISCInfo_DEBUG
                    write_log("First Toshiba command completed successfully");
                #endif

                p = (char *) cmd;
                *p++ = 0x1C;
                *p++ = 0x00;
                *p++ = 0x00;
                *p++ = 0xFF; // len
                *p++ = 0xFF;
                *p++ = 0x00;
                *p++ = 0x00;
                *p++ = 0x00;
                *p++ = 0x00;
                *p++ = 0x00;
                *p++ = 0x00;
                *p++ = 0x00;

                if (Main_Form->SPTI1->Checked)
                {
                    status = dev->SendSPTICommand(cmd, 12, dwFlags, SCSI_IOCTL_DATA_IN, (unsigned char *) buffer, 255);
                }
                else
                {
                    status = dev->SendCommand(cmd, 12, SRB_DIR_IN, (unsigned char *) buffer, 255);
                }

                if (status != 0)
                {
                    #ifdef DISCInfo_DEBUG
                        write_log("Second Toshiba command failed");
                    #endif
                    dev->if_toshiba=false;
                    dev->fw_code[0]=0;
                    dev->tosh_model[0]=0;
                } else
                {
                    #ifdef DISCInfo_DEBUG
                        write_log("Second Toshiba command completed successfully");
                    #endif
                    if ( !isalpha(buffer[6]) || !isalpha(buffer[7]) ) // special case for the SD-M1201?
                    {
                        dev->if_toshiba=false;
                        memcpy(dev->fw_code, "", 25);
                        dev->fw_code[25]=0;
                        memcpy(dev->tosh_model, "", 35);
                        dev->tosh_model[35]=0;
                    } else
                    {
                        dev->if_toshiba=true;
                        sprintf(fk,"%c%c", toupper(buffer[6]), toupper(buffer[7]));
                        memcpy(dev->fw_code, fk, 2);
                        dev->fw_code[2] = 0;
                        for (i = 0; i < (sizeof(Types2)/sizeof(Types2[0])); i++)
                        {
                            if ((Types2[i].h == toupper(buffer[6])) && (Types2[i].l == toupper(buffer[7])))
                            {
                                sprintf(dev->tosh_model,"Toshiba %s",Types2[i].desc);
                                #ifdef DISCInfo_DEBUG
                                    char logz[255];
                                    sprintf(logz,"Toshiba drive identified as %s",Types2[i].desc);
                                    write_log(logz);
                                #endif
                                foundit = 1;
                            }
                        }
                        if (foundit!=1)
                        {
                            sprintf(dev->tosh_model,"Unknown model");
                            #ifdef DISCInfo_DEBUG
                                char logz[255];
                                sprintf(logz,"Unknowned Toshiba model with code %c%c",toupper(buffer[6]),toupper(buffer[7]));
                                write_log(logz);
                            #endif
                        }
                    }
                }
            }
        } else
        {
            dev->if_toshiba=false;
            dev->fw_code[0]=0;
            dev->tosh_model[0]=0;
        }
        // END TOSHIBA DUMPING OF TWO BYTE

        if ((dev->type == DTYPE_CROM) || (dev->type == DTYPE_WORM))
        {
            #ifdef DISCInfo_DEBUG
                write_log("Issueing the Mode Sense (10) command");
            #endif
            dev->cdRRead = FALSE;
            dev->cdRWRead = FALSE;
            dev->cdMethod2Read = FALSE;
            dev->dvdRomRead = FALSE;
            dev->dvdRRead = FALSE;
            dev->dvdRWRead = FALSE;
            dev->dvdRamRead = FALSE;
            dev->dvdPRRead = FALSE;
            dev->dvdPRWRead = FALSE;
                                                
            dev->cdRWrite = FALSE;
            dev->cdRWWrite = FALSE;
            dev->testWrite = FALSE;
            dev->dvdRWrite = FALSE;
            dev->dvdRWWrite = FALSE;
            dev->dvdRamWrite  = FALSE;
            dev->dvdPRWrite  = FALSE;            
            dev->dvdPRWWrite  = FALSE;

            dev->read_s=0;
            dev->write_s=0;

            dev->audioplay  = FALSE;
            dev->composite  = FALSE;
            dev->digport1  = FALSE;
            dev->digport2  = FALSE;
            dev->mode1form  = FALSE;
            dev->mode2form  = FALSE;
            dev->multisession  = FALSE;
            dev->buffunder  = FALSE;
            dev->ISRC  = FALSE;
            dev->UPC  = FALSE;
            dev->barcode  = FALSE;
            dev->mechanism[0]  = 0;            
            dev->mtrainier = FALSE;

            dev->iscdRRead = FALSE;
            dev->iscdRWrite = FALSE;
            dev->isdvdDrive = FALSE;
            dev->iscdDrive = FALSE;

            dev->buffersize=0;
            dev->levels=0;                        

            dev->isdvdDrive = FALSE;

            memset( &s, 0, sizeof( s ) );
            memset( bx, 0xFF, 256 );
            memset(cmd, 0, sizeof(cmd));

            cmd[0] = 0x5A;
            cmd[2] = 0x3F;
            cmd[7] = 0x01;
            cmd[8] = 0x00;

            if (Main_Form->SPTI1->Checked)
            {
                status = dev->SendSPTICommand(cmd, 10, dwFlags, SCSI_IOCTL_DATA_IN, (unsigned char *) bx, 256 );
            } else
            {
                status = dev->SendCommand(cmd, 10, SRB_DIR_IN,(unsigned char *) bx, 256);
            }

            if (status != 0)
            {
                #ifdef DISCInfo_DEBUG
                    write_log("Mode Sense (10) command failed");
                #endif
            } else
            {
                #ifdef DISCInfo_DEBUG
                    write_log("Mode Sense (10) completed successfully");
                #endif
                lenData = ((unsigned int)bx[0] << 8) + bx[1];

                p = bx + 8;

                while( (p < &(bx[2+lenData])) && (p < pMax) )
                {
                    BYTE which;
                    which = p[0] & 0x3F;
                    switch( which )
                    {
                        case 0x2A:
                            memcpy( CDComp, p, p[1]+2 );

                            if(CDComp[2] & 0x01) dev->cdRRead = true;
                            if(CDComp[2] & 0x02) dev->cdRWRead = true;
                            if(CDComp[2] & 0x04) dev->cdMethod2Read = true;
                            if(CDComp[2] & 0x08) dev->dvdRomRead = true;
                            if(CDComp[2] & 0x10)
                            {
                                dev->dvdRRead = true;
                                dev->dvdRWRead = true;
                            }
                            if(CDComp[2] & 0x20) dev->dvdRamRead = true;
                            if(CDComp[3] & 0x01) dev->cdRWrite = true;
                            if(CDComp[3] & 0x02) dev->cdRWWrite = true;
                            if(CDComp[3] & 0x04) dev->testWrite = true;
                            if(CDComp[3] & 0x10) dev->dvdRWrite = true;
                            if(CDComp[3] & 0x20) dev->dvdRamWrite  = true;
                            if(CDComp[4] & 0x01) dev->audioplay = true;
                            if(CDComp[4] & 0x02) dev->composite = true;
                            if(CDComp[4] & 0x04) dev->digport1 = true;
                            if(CDComp[4] & 0x08) dev->digport2 = true;
                            if(CDComp[4] & 0x10) dev->mode1form = true;
                            if(CDComp[4] & 0x20) dev->mode2form = true;
                            if(CDComp[4] & 0x40) dev->multisession = true;
                            if(CDComp[4] & 0x80) dev->buffunder = true;
                            if(CDComp[5] & 0x20) dev->ISRC = true;
                            if(CDComp[5] & 0x40) dev->UPC = true;
                            if(CDComp[5] & 0x80) dev->barcode = true;
 
                            switch(CDComp[6] & 0xE0)
                            {
                                case 0x00:
                                    sprintf(dev->mechanism,"%s","Caddy");
                                    break;
                                case 0x20:
                                    sprintf(dev->mechanism,"%s","Tray");
                                    break;
                                case 0x40:
                                    sprintf(dev->mechanism,"%s","Popup");
                                    break;
                                case 0x60:
                                    sprintf(dev->mechanism,"%s","Unasigned");
                                    break;
                                case 0x80:
                                    sprintf(dev->mechanism,"%s","Induvidual discs changer");
                                    break;
                                case 0xA0:
                                    sprintf(dev->mechanism,"%s","Magazine mechanism changer");
                                    break;
                                case 0xC0:
                                    sprintf(dev->mechanism,"%s","Unasigned");
                                    break;
                                case 0xE0:
                                    sprintf(dev->mechanism,"%s","Unasigned");
                                    break;
                                default:
                                    ShowMessage("Unknowned "+AnsiString(dev->vendor_name));
                            }

                            if( dev->dvdRomRead ||
                                dev->dvdRRead   ||
                                dev->dvdRamRead ||
                                dev->dvdRWrite  ||
                                dev->dvdRamWrite )
                                dev->isdvdDrive = true;
                            if( dev->cdRRead       ||
                                dev->cdRWRead      ||
                                dev->cdMethod2Read ||
                                dev->cdRWrite      ||
                                dev->cdRWWrite )
                                dev->iscdDrive = true;
                            if( dev->cdRRead       ||
                                dev->cdRWRead      ||
                                dev->cdMethod2Read)
                                dev->iscdRRead = true;
                            if( dev->cdRWrite      ||
                                dev->cdRWWrite )
                                dev->iscdRWrite = true;

                                memcpy( CDComp, p, p[1]+2 );
                                calc = ((DWORD)CDComp[8] << 8) + (DWORD)CDComp[9];
                                dev->read_s=(long)calc / 175 ;
                                calc = ((DWORD)CDComp[18] << 8) + (DWORD)CDComp[19];
                                dev->write_s=(long)calc / 175 ;
                                calc = ((DWORD)CDComp[10] << 8) + (DWORD)CDComp[11];
                                dev->levels=calc;
                                calc = ((DWORD)CDComp[12] << 8) + (DWORD)CDComp[13];
                                dev->buffersize=calc;
                    }
                    p += (p[1] + 2);
                }
            }

            AnsiString capable=Trim(AnsiString(dev->name).SubString(0,24))+":\n";
            memset(cmd, 0, sizeof(cmd));

            #ifdef DISCInfo_DEBUG
                write_log("Issueing the Get Configuration command part 1");
            #endif

            cmd[0] = 0x46;
            cmd[7] = (2048 & 0xFF00) >> 8;
            cmd[8] = (2048 & 0x00FF);

            if (Main_Form->SPTI1->Checked)
            {
                status = dev->SendSPTICommand(cmd, 10, dwFlags, SCSI_IOCTL_DATA_IN, (unsigned char *) buffer, 2048 );
            }
            else
            {
                status = dev->SendCommand(cmd, 10, SRB_DIR_IN, (unsigned char *) buffer, 2048 );
            }

            if (status != 0)
            {
            #ifdef DISCInfo_DEBUG
                write_log("Get Configuration command part 1 failed");
            #endif
            } else
            {
                #ifdef DISCInfo_DEBUG
                    write_log("Get Configuration command part 1 completed successfully");
                #endif
                Length =  buffer[0] << 24 | buffer[1] << 16 | buffer[2] <<8 | buffer[3];
                AdditionalLength = buffer[11];
                NumberofProfiles = AdditionalLength / 4;

                int offset = 12;  //first feature offset in buffer MSB
                for(int f=0; f < NumberofProfiles; f++)
                {
                    int profile = buffer[offset] << 8 | buffer[offset + 1];
                    switch (profile)
                    {
                        case 3:
                        case 5:     capable += "asynchronous magneto optical\n"; break;
                        case 8:     capable += "cdrom read\n"; break;
                        case 9:     capable += "cdr  write\n"; break;
                        case 0xA:   capable += "cdrw  write\n"; break;
                        case 0x10:  capable += "dvdrom read\n"; break;
                        case 0x11:  capable += "dvd-r write\n";
                                    dev->dvdRWrite=true; dev->dvdRRead=true;
                                    break;
                        case 0x12:  capable += "dvd-ram write\n"; break;
                        case 0x13:  capable += "dvd-rw restricted overwrite\n";
                                    dev->dvdRWWrite=true; dev->dvdRWRead=true;
                                    break;
                        case 0x14:  capable += "dvd-rw sequential recording\n";
                                    dev->dvdRWWrite=true; dev->dvdRWRead=true;
                                    break;
                        case 0x1A:  capable += "dvd+rw write\n";
                                    dev->dvdPRWWrite=true; dev->dvdPRWRead=true;
                                    break;  //make some assumptions here if write then read too
                        case 0x1B:  capable += "dvd+r write\n";
                                    dev->dvdPRWrite=true; dev->dvdPRRead=true;
                                    break;     //and here if write then read too
                        case 0xFFFF: capable += "Not good\n"; break;
                    }
                    offset += 4;
                    Length -= 4;
                    if (Length <= 12 || offset >= 2048)
                    break;
                }
                capable += "\n";
            }
            
            // Mt. Rainier

            memset(cmd, 0, sizeof(cmd));
            memset(buffer, 0, sizeof(buffer));

            #ifdef DISCInfo_DEBUG
                write_log("Issueing the Get Configuration command part 2");
            #endif

            cmd[0] = 0x46;
            cmd[3] = 1;            
            cmd[7] = (2048 & 0xFF00) >> 8;
            cmd[8] = (2048 & 0x00FF);

            if (Main_Form->SPTI1->Checked)
            {
                status = dev->SendSPTICommand(cmd, 10, dwFlags, SCSI_IOCTL_DATA_IN, (unsigned char *) buffer, 2048 );
            }
            else
            {
                status = dev->SendCommand(cmd, 10, SRB_DIR_IN, (unsigned char *) buffer, 2048 );
            }

            if (status != 0)
            {
                #ifdef DISCInfo_DEBUG
                    write_log("Get Configuration command part 2 failed");
                #endif
            } else
            {
                #ifdef DISCInfo_DEBUG
                    write_log("Get Configuration command part 2 completed successfully");
                #endif
                Length =  buffer[0] << 24 | buffer[1] << 16 | buffer[2] <<8 | buffer[3];
                AdditionalLength = buffer[11];
                NumberofProfiles = AdditionalLength / 4;

                offset = 8;  //first feature offset in buffer MSB
                do
                {
                    int feature = buffer[offset] << 8 | buffer[offset + 1];
                    switch (feature)
                    {
                        case 0x28:  capable += "mt rainier read write\n";
                                    dev->mtrainier=true; break;
                        case 0x2B:  capable += "dvd+r read\n";
                                    dev->dvdPRRead=true;
                                    break;
                        case 0x2A:  capable += "dvd+rw read\n";
                                    dev->dvdPRWRead=true; dev->dvdPRRead=true;
                                    break;
                        case 0xFFFF: capable += "Not good\n"; break;
                    }
                    offset += (4 + buffer[offset + 3]);
                } while(offset < (Length - 4));
            }
            //ShowMessage(capable);
            //fwrite(buffer, 2048, 1, fx);
            //fwrite("YYYXXX", 6, 1, fx);
        }
        if ((dev->type == DTYPE_CROM) || (dev->type == DTYPE_WORM))
        {

            // Serial number
            dev->serial[0]=0;

       		memset((void *) CDB, 0, sizeof(CDB));
            memset(buffer, 0, sizeof(buffer));

            #ifdef DISCInfo_DEBUG
                write_log("Issueing the Get Configuration command (SN)");
            #endif

            CDB[0] = 0x46; // Get Configuration
            CDB[2] = (0x108 & 0xFF00) >> 8;
            CDB[3] = (0x108 & 0xFF);
            CDB[7] = 0;
            CDB[8] = 30;

            if (Main_Form->SPTI1->Checked)
            {
                status = dev->SendSPTICommand(CDB, 10, dwFlags, SCSI_IOCTL_DATA_IN, (unsigned char *) buffer, 50 );
            }
            else
            {
                status = dev->SendCommand(CDB, 10, SRB_DIR_IN, (unsigned char *) buffer, 50 );
            }

            if (status != 0)
            {
            #ifdef DISCInfo_DEBUG
                write_log("Get Configuration command (SN) command failed");
            #endif
            } else
            {
                #ifdef DISCInfo_DEBUG
                    write_log("Get Configuration command (SN) command completed successfully");
                #endif
                AnsiString serial="";
                int len = 12;
                char ch;
                bool isOK;
                for (int i = 0; i < len; i++)
                {
                    ch = buffer[12+i];
                    if (ch >= 0x20 && ch <= 0x7e && ch != ' ')
                    {
                        serial += ch;
                        isOK=true;
                    }
                    else
                    break;
                }
                dev->serial[12]=0;

                if (isOK)
                {
               		sprintf(dev->serial,serial.c_str());
        //            ShowMessage(dev->serial);
        //            fwrite(buffer, 50, 1, fx);
                }
            }
        }
        dev->drive_status=false;
    	dev->region_status[0]=0;
    	dev->user=0;
    	dev->manufactor=0;
    	dev->current_region[0]=0;

        if (dev->type == DTYPE_CROM && dev->type != DTYPE_WORM && dev->isdvdDrive)
        {
            #ifdef DISCInfo_DEBUG
                write_log("Issueing the Report Key command");
            #endif
            memset(cmd, 0, sizeof(cmd));
            memset(buffer, 0, sizeof(buffer));
            cmd[0] = 0xA4;
            cmd[9] = 0x08;
            cmd[10] = 0x08;

            if (Main_Form->SPTI1->Checked)
            {
                status = dev->SendSPTICommand(cmd, 12, dwFlags, SCSI_IOCTL_DATA_IN, (unsigned char *) buffer, 8 );
            }
            else
            {
                status = dev->SendCommand(cmd, 12, SRB_DIR_IN, (unsigned char *) buffer, 8 );
            }

            buffer[8]=0;

            if (status != 0)
            {
                dev->drive_status=false;
                #ifdef DISCInfo_DEBUG
                    write_log("Report Key command failed (RPC-1)");
                #endif
            } else
            {
                #ifdef DISCInfo_DEBUG
                    write_log("Report Key command completed successfully (RPC-2)");
                #endif
                dev->drive_status=true;

                switch (buffer[5])
                {
                    case 0xFF:
                        r_mask[0]="Not set";
                        r_mask[1]=0;
                        break;
                    case 0xFE:
                        r_mask[0]="1";
                        r_mask[1]=0;
                        break;
                    case 0xFD:
                        r_mask[0]="2";
                        r_mask[1]=0;
                        break;
                    case 0xFB:
                        r_mask[0]="3";
                        r_mask[1]=0;
                        break;
                    case 0xF7:
                        r_mask[0]="4";
                        r_mask[1]=0;
                        break;
                    case 0xEF:
                        r_mask[0]="5";
                        r_mask[1]=0;
                        break;
                    case 0xDF:
                        r_mask[0]="6";
                        r_mask[1]=0;
                        break;
                    case 0xBF:
                        r_mask[0]="7";
                        r_mask[1]=0;
                        break;
                    case 0x7F:
                        r_mask[0]="8";
                        r_mask[1]=0;
                        break;
                    default:
                        r_mask[0]="n/a";
                        r_mask[1]=0;
                }

                //***********************************************
                char *msg1[4]={ "Not Set", "Set", "Last Chance", "Permanent"};
                flags = (buffer[4] >> 6) & 3; // this extracts bit fields
                resets = (buffer[4] >> 3) & 7;
                changes = (buffer[4] & 7);
                //***********************************************
                if (flags>=0 && flags<=3)
                {
                    memcpy(dev->region_status,msg1[flags],30);
                } else
                {
                    memcpy(dev->region_status,"n/a",30);
                }
                dev->user=changes;
                dev->manufactor=resets;
                sprintf(dev->current_region,"%s",r_mask[0]);
            }
        } else
        {
            dev->drive_status=false;
        }
    }
//    fclose(fx);
    #ifdef DISCInfo_DEBUG
        write_log("---------------------------------------------");
    #endif
    return 0;
}

// Sends an ASPI command
DWORD Device::SendCommand(BYTE *CDBByte, BYTE CDBLen, BYTE SRB_Flags,
	BYTE *BufPointer, DWORD BufLen) const
{
	// Create the event if it doesn't exist yet
	if (!event)
		event = CreateEvent(NULL, TRUE, FALSE, NULL);
	ResetEvent(event);

	// Initialize structure
	SRB_ExecSCSICmd srb;

	memset((void *) &srb, 0, sizeof(srb));

	srb.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srb.SRB_HaId = this->HaId;
	srb.SRB_Flags = SRB_Flags | SRB_EVENT_NOTIFY;
	srb.SRB_Target = this->Target;
	srb.SRB_Lun = this->Lun;
	srb.SRB_BufLen = BufLen;
	srb.SRB_BufPointer = BufPointer;
	srb.SRB_SenseLen = SENSE_LEN;
	srb.SRB_CDBLen = CDBLen;
	srb.SRB_PostProc = (void *) event;
	
	memcpy((void *) srb.CDBByte, (void *) CDBByte, CDBLen);

	// Execute command
	DWORD ASPIStatus = SendASPI32Command(&srb);

	if (ASPIStatus == SS_PENDING)
		WaitForSingleObject(event, INFINITE);

	// Check for errors
	if (srb.SRB_Status != SS_COMP)
	{
		DWORD temp = ((srb.SenseArea[2] & 0x0F) << 16) | (srb.SenseArea[12]
			<< 8) | (srb.SenseArea[13]);

		// If sense data makes no sense
		if (!temp)
			temp = (srb.SRB_Status << 24) | (srb.SRB_HaStat << 16) |
				(srb.SRB_TargStat << 8);

		if (!temp)
			temp = 0x04000000;
		return temp;
	}
	return 0;
}

// Sends a SPTI command
DWORD Device::SendSPTICommand(BYTE *CDBByte, BYTE CDBLen, DWORD dwFlags, DWORD InOut,
    BYTE *BufPointer, DWORD BufLen) const
{
        HANDLE hDrive;
        char bufec[32];
        int retVal = 0;
        DWORD dwReturned;
        SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER swb;

        wsprintf( bufec, "\\\\.\\%s:", this->letter);
//        ShowMessage(AnsiString(this->letter));        
        hDrive = CreateFile( bufec, dwFlags, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                              OPEN_EXISTING, 0, NULL );
        if ( hDrive == INVALID_HANDLE_VALUE )
//            ShowMessage("Invalid handle!!! ");
//            return 3;

        dwReturned = 0;

        ZeroMemory( &swb, sizeof(swb) );
        swb.spt.Length          = sizeof(SCSI_PASS_THROUGH);
        swb.spt.CdbLength       = CDBLen;
        swb.spt.DataIn          = InOut;
        swb.spt.DataTransferLength = BufLen;
        swb.spt.TimeOutValue    = 5;
        swb.spt.DataBuffer      = BufPointer;
        swb.spt.SenseInfoOffset =
          offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);
        memcpy((void *) swb.spt.Cdb, (void *) CDBByte, CDBLen);

        if ( !DeviceIoControl( hDrive,
                                IOCTL_SCSI_PASS_THROUGH_DIRECT,
                                &swb,
                                sizeof(swb.spt),
                                &swb,
                                sizeof(swb),
                                &dwReturned,
                                FALSE ) )

            retVal = -1;
        CloseHandle(hDrive);
        hDrive=NULL;
        if ( retVal < 0 )
        {
          DWORD dwError = GetLastError();
          if ( dwError == 5 ) {
            ShowMessage( " Error: you must have Administor priveleges to use SPTI under Win2000 ");
          } else if ( dwError == 1117 ) {
            //ShowMessage("Error 1117");
          } else {
          }
          return dwError;
        }
	return 0;
}

