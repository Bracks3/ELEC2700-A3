/*_____________________________________________________________________________________________________________________

        Project:        ELEC2700 Assignment 3 template
        Module:         A3_XX.c
        Author:         Josh Brackenbury and Michael Dobbins
        Date:           06-06-13

        Description:    A program simulating the functionality of an mp3 player, written to be run on an 8051.
        		
        		Functions (e.g. play/pause/volume) can be accessed through pressing buttons 1-4 
        		Songs can be uploaded/downloaded through the interface 
        
        		
        

        Notes:          

        Revisions:

		Status: Working


_______________________________________________________________________________________________________________________*/

#include <c8051f120.h>     // SFR declarations
#include "A3_XX.h"
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>	    //string info
#include <string.h>
	

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Main

        Description:      Main routine

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void main(void)
{
		
	
	
	unsigned var,c;
	General_Init();
	Volume = 0x3F;			// Nominal volume value
	LED7 = 1;               // LED 1   
	LED8 = 1;               // LED 2
	LED9 = 0;               // LED 3
	LED10 = 0;				// LED 4
	var = 0;

	//Intro Message for JPod(Innovation)

	/* SSD for jP */
	TRIG = 1;
	P2 = 0xE1;
	TRIG = 0;
	P2 = 0x8C;
	Delay(145);
	/* SSD for Po */
	TRIG = 1;
	P2 = 0x8C;
	TRIG = 0;
	P2 = 0xA3;
	Delay(145);
	/* SSD for oD */
	TRIG = 1;
	P2 = 0xA3;
	TRIG = 0;
	P2 = 0xA1;
	Delay(145);
	/* SSD for "D " */
	TRIG = 1;
	P2 = 0xA1;
	TRIG = 0;
	P2 = 0xFF;
	Delay(145);
	/* SSD for " " */
	TRIG = 1;
	P2 = 0xFF;
	TRIG = 0;
	P2 = 0xFF;
	Delay(290);
		
	State(1); 
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         State 

        Description:      State switch

        Revisions:        Added new states as they were created

--------------------------------------------------------------------------------------------------------------------*/
void State(int i)
{
	// State switch selector
	switch( i ) 
	{	
    case 0:
		Play(); //  move to play state
        break;
    case 1:
		Stop();  //  move to stop state
        break;
    case 2:
		Pause();  //  move to pause state
        break;
	}

}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Play

        Description:      Play State
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/
void Play()
{
	int shuffle = 0;
	while (1)
	{
		strcpy(str, "                                ");
		if (shuffle == 1)
			selection = RandomNum();
		switch( selection ) 
		{	
			case 0:
				strcpy(str, "Mary Had A Little Lamb"); // string for SSD 
				PlayInit();
				Mary_Had_A_Little_Lamb();
		        break;
		    case 1:
				strcpy(str, "Twinkle Twinkle Little Star");// string for SSD 
				PlayInit();
				Twinkle_Twinkle_Little_Star();
		        break;
		    case 2:
				strcpy(str, "Flintstones");// string for SSD 
				PlayInit();
				Flintstones();
		        break;
			case 3:
				strcpy(str, "Saregama");// string for SSD 
				PlayInit();
				Saregama();
				break;
			case 4:
				strcpy(str, "Beethoven");// string for SSD 
				PlayInit();
				BeethovenPlay();
				break;
			case 5:
				strcpy(str, "Adams Family");// string for SSD 
				PlayInit();
				AdamsFamily();
				break;
			case 6: // SHUFFLE INNOVATION
				// randomly select song
				if (shuffle == 0)
				{
					shuffle = 1; // turn shuffle on
					// SSD "Shuffle"			
					TRIG = 1;
					P2 = SSS; // First letter for scrolling
					TRIG = 0;
					P2 = SSh;
					Delay(290);
				}
				else if (shuffle == 1)
					shuffle = 0;
				break;
		}
		if (selection == 5)
			selection = 0;
		else
			selection++;
	}

}
			
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Stop

        Description:      Stop State
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/


void Stop()
{
	j=0;
	Letter1 = 0xFF;
	TRIG = 1;
	P2 =  Letter1;
	LetterCheckSSD(j); // First letter for scrolling
	TRIG = 0;
	P2 = Letter2;
	Delay(90);
		
	while(1)
	{

		if(S1 == 0 && S4 == 0 ) // if both s1 and s4 are pressed
		{	
			button_debounce();
			Computer_Interface(); // Launch the computer interface
		}
		if(S2 == 0 && S3 == 0 ) // if both s2 and s3 are pressed
		{	
			button_debounce();
			selection = 6;
			strcpy(str, "Shuffle");
			State(0);
		}
		if(S1 == 0)
		{	
			button_debounce();	// temp button debounce	
			VolumeControl(1); /* volume down */
		}
		if(S2 == 0)
		{	
			button_debounce();			
			VolumeControl(0); /* volume up */
		}
		if(S3 == 0)
		{		
			button_debounce();		
			State(0); /* Play */
		}
		if(S4 == 0) // Change song
		{	
			button_debounce();
			selection++;
			j=0;
			Letter1 = 0xFF;

				if (selection > 5) // if you have reached the end of the song list
				{
					selection = 0; // go back to the start of the song list
				}
			
				if (selection == 0) 
				{
						strcpy(str, "Mary Had A Little Lamb");
				}
				if (selection == 1) 
				{
						strcpy(str, "Twinkle Twinkle Little Star");
				}
				if (selection == 2) 
				{
						strcpy(str, "Flintstones");
				
				}
				if (selection == 3) 
				{
						strcpy(str, "Saregama");
				
				}
				if (selection == 4) 
				{
						strcpy(str, "Beethoven");
				
				}
				if (selection == 5) 
				{
						strcpy(str, "Adams Family");
				
				}
				

		}
	
				  	
	
				
	   /* SSD for Song Titles */
		 // local variable
		
		arrayLengthnum = strlen(str); // Checks lenght of array str
		LetterCheckSSD(j);
		if (j < arrayLengthnum)
		{
			TRIG = 1;
			P2 =  Letter1; // First letter for scrolling
			TRIG = 0;
			P2 = Letter2;
			Delay(145);
			Letter1 = Letter2;	
			//arrayLengthnum = strlen(str);
			j++;
		}
		if (j == arrayLengthnum)
		{
				TRIG = 1;
				P2 =  Letter1; // Last letter for scrolling
				TRIG = 0;
				P2 = 0xFF;
				Delay(145);
				j = 0; // go back to the start of the song list
				TRIG = 1;
				P2 =  0xFF; // Last letter for scrolling
				TRIG = 0;
				P2 = 0xFF;
				Delay(145);
				Letter1 = 0xFF;
		}

		
	    			
			
		

	} //end while
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Pause

        Description:      Pause State
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/
void Pause()
{		
	/* SSD for PS */
		TRIG = 1;
		P2 = 0x8C;
		TRIG = 0;
		P2 = 0x92;			
	while (1)
	{

		if(S1 == 0)
		{	
			button_debounce();	// temp button debounce	
			VolumeControl(1); /* volume down */
		}
		if(S2 == 0)
		{	
			button_debounce();			
			VolumeControl(0); /* volume up */
		}

		if (S3 == 0)
		{
			button_debounce();

			break;
		}
		if(S4 == 0)
		{	
			button_debounce();	
			State(1); /* Stop */
			break;			
			
		}
	}
	return;
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Computer Interface

        Description:      UART State
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/
void Computer_Interface()
{			
		int i;
		unsigned var;
		Volume = 0x3F;			// Nominal volume value

		TRIG = 1;
		P2 = SSc;
		TRIG = 0;
		P2 = SSt;
		
		var = 0;

		UARTInit();		// UART Intialise settings

		i = 0;
		while (i < 10)
		{
			TI0=1;
			printf("\n");
			i++;
		}

	printf("*---------------------------------------------------------------------------------------------*\n");
	printf("*                                    JPOD MENU                                                *\n");
	printf("* 0 : Quit                                                                                    *\n");
	printf("*                                                                                             *\n");
	printf("* 1 : Play Song                                                                               *\n");
	printf("*                                                                                             *\n");
	printf("* 2 : Upload Song                                                                             *\n");
	printf("*                                                                                             *\n");
	printf("* 3 : Download Song                                                                           *\n");
	printf("*                                                                                             *\n");
	printf("* 4 : Keyboard                                                                                *\n");
	printf("*                                                                                             *\n");
	printf("*---------------------------------------------------------------------------------------------*\n");
		
		TI0 = 0;
		while(1)
		{
				
			if (RI0)
			{
				var = SBUF0; // read in user input
				RI0 = 0;
			}
			if (var == 0x30)
			{
				// Clear Screen
				while (i < 100)
				{
					TI0=1;
					printf("\n");
					i++;
				}
				// Return to stop state
				State(1);
			}
			if (var == 0x31)
			{
				SongMenu(); // got to stop menu
			}
			if (var == 0x32)
			{
				UploadSong(); // go to upload song
			}
			if (var == 0x33)
			{
				DownloadSong();// Download Song 
			}
			if (var == 0x34)
			{
				
				printf("*---------------------------------------------------------------------------------------------*\n");
				printf("*                                      KEYBOARD!!                                             *\n");		
				printf("*           Press keys on the bottom row of your keyboard (0 to exit)                         *\n");
				printf("*                                                                                             *\n");		
				printf("*---------------------------------------------------------------------------------------------*\n");
				Keyboard();
			}
		}
		
}

void SongMenu()
{
	unsigned var;
		TI0 = 1;
		var = 0;
		printf("*---------------------------------------------------------------------------------------------*\n");
		printf("*                                    SONG MENU                                                *\n");
		printf("* 0 : Back to Main Menu                                                                       *\n");
		printf("*                                                                                             *\n");
		printf("* 1 : Mary Had A Little Lamb                                                                  *\n");
		printf("*                                                                                             *\n");
		printf("* 2 : Twinkle Twinkle Little Star                                                             *\n");
		printf("*                                                                                             *\n");
		printf("* 3 : Flintstones                                                                             *\n");
		printf("*                                                                                             *\n");
		printf("* 4 : Saregama                                                                                *\n");
		printf("*                                                                                             *\n");
		printf("* 5 : Beethoven                                                                               *\n");
		printf("*                                                                                             *\n");
		printf("* 6 : Adams Family                                                                            *\n");
		printf("*                                                                                             *\n");
		printf("* 7 : Shuffle                                                                                 *\n");
		printf("*                                                                                             *\n");
		printf("*---------------------------------------------------------------------------------------------*\n");
			
		TI0 = 0;
		while(1)
		{
				
			if (RI0)
			{
				var = SBUF0; // read in user input
				RI0 = 0;
			}
			if (var == 0x30)
			{
				RI0 = 1;
				Computer_Interface(); // return to main
			}

			//Play songs
			if (var == 0x31)
			{
				printf("Now Playing: Mary Had A Little Lamb\n");		
				selection = 0;
				Play();
			}
			if (var == 0x32)
			{
				printf("Now Playing: Twinkle Twinkle Little Star  \n");
				selection = 1;
				Play();
			}
			if (var == 0x33)
			{
				printf("Now Playing: Flintstones\n");
				selection = 2;
				Play();
			}
			if (var == 0x34)
			{
				printf("Now Playing: Saregama\n");
				selection = 3;
				Play();
			}
			if (var == 0x35)
			{
				printf("Now Playing: Beethoven\n");
				selection = 4;
				Play();
			}
			if (var == 0x36)
			{
				printf("Now Playing: Adams Family\n");
				selection = 5;
				Play();
			}

			// Start in shuffle mode
			if (var == 0x37)
			{
				printf("Now Shuffling\n");
				selection = 6;
				Play();
			}

		}
}

void DownloadSong()
{	
	xdata unsigned var1;
	var1 = 0;
	TI0 = 1;
	printf("*---------------------------------------------------------------------------------------------*\n");
	printf("*                                      DOWNLOAD                                               *\n");		
	printf("*           Please choose a song to download into the specified format now                    *\n");
	printf("*                                                                                             *\n");		
	printf("* 0 : Back to Main Menu                                                                       *\n");
	printf("*                                                                                             *\n");
	printf("* 1 : Mary Had A Little Lamb                                                                  *\n");
	printf("*                                                                                             *\n");
	printf("* 2 : Twinkle Twinkle Little Star                                                             *\n");
	printf("*                                                                                             *\n");
	printf("* 3 : Flintstones                                                                             *\n");
	printf("*                                                                                             *\n");
	printf("* 4 : Adams Family                                                                            *\n");
	printf("*                                                                                             *\n");
	printf("*---------------------------------------------------------------------------------------------*\n");
			
	
	//counter = 0; 

	TI0 = 0;

	while(1)
	{			
		if (RI0)
		{
			var1 = SBUF0; // read in user input
			RI0 = 0;
		}
		if (var1 == 0x30)
		{
			//RI0 = 1;
			Computer_Interface(); // return to main
		}
			//Play songs
		if (var1 == 0x31)
		{
			printf("Now Downloading: Mary Had A Little Lamb\n");	
			Download(1);	
		}
		if (var1 == 0x32)
		{
			printf("Now Downloading: Twinkle Twinkle Little Star\n");
			Download(2);
		}
		if (var1 == 0x33)
		{
			printf("Now Downloading: Flintstones\n");
			Download(3);
		}
		if (var1 == 0x34)
		{
			printf("Now Downloading: Adams Family\n");
			Download(4);
		}

		
	}

	
}

void Download(int a)
{
	
/*	FILE *f = fopen("download.txt, "w");
	if (f == null)
	{
		printf("Error opening file! Please check that download.txt exists");
	}
	else
	{	
		
	}
*/
	switch( a ) 
	{	
		case 1:	printf(":Mary Had A Little Lamb#E1 D1 C1 D1 E1 E1 E2 D1 D1 D2 E1 G1 G2 E1 D1 C1 D1 E1 E1 E1 E1 D1 D1 E1 D1 C4 !\n");
				break;
		case 2:	printf(":Twinkle Twinkle Little Star#C1 C1 G1 G1 A1 A1 G2 F1 F1 E1 E1 D1 D1 C2 G1 G1 F1 F1 E1 E1 D2 G1 G1 F1 F1 E1 E1 D2 C1 C1 G1 G1 A1 A1 G2 F1 F1 E1 E1 D1 D1 C2 !\n");
				break;
		case 3:	printf(":Flintstones#notes!\n");
				break;
		case 4:	printf(":Adams Family#notes!\n");
				break;
	}

	printf("Download Complete! Please save to text file\n");
	TI0 = 1;
	Computer_Interface();
}

void UploadSong()
{	
	xdata unsigned Upload[198];
	xdata char convert[198];
	xdata unsigned var;
	int i = 0;
	int convertCount = 0;
	
	
	TI0=1;
	printf("*---------------------------------------------------------------------------------------------*\n");
	printf("*                                      UPLOAD                                                 *\n");		
	printf("*           Please upload a text file in the specified format now                             *\n");
	printf("*                                                                                             *\n");		
	printf("*---------------------------------------------------------------------------------------------*\n");
	
	printf(" \n");
	counter = 0; 

	TI0 = 0;

	while(1)
	{			
		if (RI0)
		{
			var = SBUF0;
			Upload[counter] = var;
			counter++;
			RI0 = 0;

			if (var == 0x21)
			{
				// convert ascii to char
				for (i=0; i<arraySize; i++)
				{
					convert[i] = Upload[i];			
				}
				
				printf("\n Upload Complete! ");
				TI0 = 0;
				RI0 = 1;
				PlayUpload(convert);
			}

		}
		
	}




}

void PlayUpload(char a[])	// Song for Upload played at this point
{
	int hash = 0;			// Varaible declared to find where the song title ends in upload file and changes to notes
	int j = 0;				// Local variable
	int k = 0;				// Local variable
	

	printf("Now Playing: ");
	for (j = 1; j < arraySize; j++)
	{
		if (a[j] == '#')
		{
			printf("%c",a[j-1]);
			hash = j;			
			break;
		} 
		else
		{
			printf("%c",a[j]); // print song uploaded and playing
			str[j] = a[j];
		}
	}

	// Play notes
	k = hash + 1; // start from the first note after the hash
	TI0 = 0;
	
	PlayInit(); // initialize play mode


	while (k < arraySize)
	{
		j = a[k+1] - '0'; // char to int for play length time
		
		if (a[k] ==  '!') // if it is the end char
		{
			RI0 = 1;
			Computer_Interface(); // return to main
		}
		else // else play the note
		{
			Delay(50);
			switch (a[k])
			{
				case 'A': NotePlay(pitch_A5, j);
						break;
				case 'B': NotePlay(pitch_B5, j);
						break; 
				case 'C': NotePlay(pitch_C5, j);
						break;
				case 'D': NotePlay(pitch_D5, j);
						break;
				case 'E': NotePlay(pitch_E5, j);
						break;
				case 'F': NotePlay(pitch_F5, j);
						break;
				case 'G': NotePlay(pitch_G5, j);
						break;
			
			}
		}
		k = k + 3; // move to next note

	}

}


void Keyboard(void)
{
	unsigned var;
	int i = 0;

	/*for (i = 0; i < 30; i++)
	{
		str[i] = "";
	}*/

	PlayInit(); // initialize play mode


	i = 0; // reset counter
	TI0 = 0;
	
	//KeyboardPlay(1);
	//KeyboardPlay(2);
	//KeyboardPlay(3);
	
	
		RI0 = 0;
		TI0 = 0;
		var = 0;

		while(1)

		{

			if (RI0)
			{
				var = SBUF0; // read in user input
				RI0 = 0;
			}
			if (var == 0x30)
			{
				i = 0;
				// Clear Screen
				while (i < 100)
				{
					TI0=1;
					printf("\n");
					i++;
				}
				Computer_Interface(); // return to main
			}
			if (var == 0x31) // z
			{
				printf("A\n");
				str[0] = 'A';
				KeyboardPlay(1);
				
				break;
			}
			if (var == 0x32) // x
			{
				printf("B\n");
				KeyboardPlay(2);
				break;
			}
			if (var == 0x33) // c
			{
				printf("C\n");
				KeyboardPlay(3);
				break;
			}
			if (var == 0x34) // v
			{
				printf("D\n");
				KeyboardPlay(4);
				break;
			}
			if (var == 0x35) // b
			{
				printf("E\n");
				KeyboardPlay(5);
				break;
			}
			if (var == 0x36) // n
			{
				printf("F\n");
				KeyboardPlay(6);
				break;
			}
			if (var == 0x37) // m
			{
				printf("G\n");
				KeyboardPlay(7);
				break;
			}
			var = 0;
		}

	Computer_Interface(); // return to main
}

void KeyboardPlay(int a)
{


		switch (a)
		{	
			case 0: 
					break;
			case 1: NotePlay(pitch_A5, 1);				
					break;
			case 2: NotePlay(pitch_B5, 1);
					break; 
			case 3: NotePlay(pitch_C5, 1);
					break;
			case 4: NotePlay(pitch_D5, 1);
					break;
			case 5: NotePlay(pitch_E5, 1);
					break;
			case 6: NotePlay(pitch_F5, 1);
					break;
			case 7: NotePlay(pitch_G5, 1);
					break;
	
		}

	Keyboard();

}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         UART Intialise Settings

        Description:      
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/
void UARTInit()
{
		SFRPAGE   = UART0_PAGE;
    	SCON0     = 0x50;
		
    	SFRPAGE   = TIMER01_PAGE;
    	TMOD      = 0x20;
   	 	CKCON     = 0x10;
    	TH1       = 0xF6;
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Play Song Intialise Interrupts and SSD

        Description:      
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/
void PlayInit()
{	
	count = 2;	// Counter used to slow down scrolling speed in play mode
	
	EIE2      = 0x04;

	j=0;
	Letter1 = 0xFF;
	TRIG = 1;
	P2 =  Letter1;
	LetterCheckSSD(j); // First letter for scrolling
	TRIG = 0;
	P2 = Letter2;
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         RandomNum

        Description:      Returns a random integer for shuffle mode
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/
int RandomNum()
{

	return rand() % 5 + 1;	

}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Volume Control

        Description:      increases/decreases volume based on user input
        Revisions:        

--------------------------------------------------------------------------------------------------------------------*/
void VolumeControl(int updown)
{
	if (updown == 0)
	{
		volumeSelect++;
		if (volumeSelect > 9) // if you have reached max volume
		{
			volumeSelect = 9; // keep at max
		}
	}
	else if (updown == 1)
	{
		volumeSelect--;
		if (volumeSelect < 0) // if you have reached min volume
		{
			volumeSelect = 0; // keep at min
		}
	}



	switch( volumeSelect ) 
	{	
		case 0:
			Volume=0x00;			// new volume value	
			LED7 = 0;               // LED 1   
			LED8 = 0;               // LED 2
			LED9 = 0;               // LED 3
			LED10 = 0;				// LED 4
	        break;
	    case 1:
			Volume=0x1F;			// new volume value	
			LED7 = 0;               // LED 1   
			LED8 = 0;               // LED 2
			LED9 = 0;               // LED 3
			LED10 = 0;				// LED 4
	        break;
	    case 2:
			Volume=0x2F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 0;               // LED 2
			LED9 = 0;               // LED 3
			LED10 = 0;				// LED 4
	        break;
		case 3:
			Volume=0x3F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 0;               // LED 2
			LED9 = 0;               // LED 3
			LED10 = 0;				// LED 4;
			break;
		case 4:
			Volume=0x4F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 1;               // LED 2
			LED9 = 0;               // LED 3
			LED10 = 0;				// LED 4
			break;
		case 5:
			Volume=0x5F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 1;               // LED 2
			LED9 = 0;               // LED 3
			LED10 = 0;				// LED 4
	        break;
	    case 6:
			Volume=0x6F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 1;               // LED 2
			LED9 = 1;               // LED 3
			LED10 = 0;				// LED 4
	        break;
		case 7:
			Volume=0x7F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 1;               // LED 2
			LED9 = 1;               // LED 3
			LED10 = 0;				// LED 4;
			break;
		case 8:
			Volume=0x8F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 1;               // LED 2
			LED9 = 1;               // LED 3
			LED10 = 1;				// LED 4
			break;
		case 9:
			Volume=0x9F;			// new volume value	
			LED7 = 1;               // LED 1   
			LED8 = 1;               // LED 2
			LED9 = 1;               // LED 3
			LED10 = 1;				// LED 4;
			break;
		

	}
	

}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         LetterCheckSSD

        Description:     Reads Character in Arrays or strings and outputs which SSD for that 
						letter into global variable Letter2 

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void LetterCheckSSD(int j)
{
	
		if(str[j]=='a'||str[j]=='A')
		{	
			Letter2=SSA;
			
		}
		if(str[j]=='b'||str[j]=='B')
		{	
						
			Letter2=SSb;
			
		}
		if(str[j]=='c'||str[j]=='C')
		{		
				
			Letter2=SSc;
			
		}
		if(str[j]=='d'||str[j]=='D')
		{		
				
			Letter2=SSd;
		}
		if(str[j]=='e'||str[j]=='E')
		{	
			Letter2=SSE;
		
		}
		if(str[j]=='f'||str[j]=='F')
		{	
						
			Letter2=SSF;
			
		}
		if(str[j]=='g'||str[j]=='G')
		{		
				
			Letter2=SSG;
			
		}
		if(str[j]=='h'||str[j]=='H')
		{		
				
			Letter2=SSh;
			
		}
		if(str[j]=='i'||str[j]=='I')
		{	
			Letter2=SSi;
			
		}
		if(str[j]=='j'||str[j]=='J')
		{	
						
			Letter2=SSJ;
			
		}
		if(str[j]=='k'||str[j]=='K')
		{		
				
			Letter2=SSK;
			
		}
		if(str[j]=='l'||str[j]=='L')
		{		
				
			Letter2=SSL;
			
		}
		if(str[j]=='m'||str[j]=='M')
		{	
			Letter2=SSM;
			
		}
		if(str[j]=='n'||str[j]=='N')
		{	
						
			Letter2=SSn;
			
		}
		if(str[j]=='o'||str[j]=='O')
		{		
				
			Letter2=SSo;
			
		}
		if(str[j]=='p'||str[j]=='P')
		{		
				
			Letter2=SSp;
			
		}
		if(str[j]=='q'||str[j]=='Q')
		{	
						
			Letter2=SSq;
			
		}
		if(str[j]=='r'||str[j]=='R')
		{		
				
			Letter2=SSr;
			
		}
		if(str[j]=='s'||str[j]=='S')
		{		
				
			Letter2=SSS;
			
		}
		if(str[j]=='t'||str[j]=='T')
		{	
			Letter2=SSt;
			
		}
		if(str[j]=='u'||str[j]=='U')
		{	
						
			Letter2=SSu;
			
		}
		if(str[j]=='v'||str[j]=='V')
		{		
				
			Letter2=SSv;
			
		}
		if(str[j]=='w'||str[j]=='W')
		{		
				
			Letter2=SSW;
			
		}
		if(str[j]=='x'||str[j]=='X')
		{	
			Letter2=SSX;
		
		}
		if(str[j]=='y'||str[j]=='Y')
		{	
						
			Letter2=SSY;
			
		}
		if(str[j]=='z'||str[j]=='Z')
		{		
				
			Letter2=SSZ;
		
		}
		if(str[j]==' ')
		{	
			Letter2=0xFF;
		}		

	

}



/*--------------------------------------------------------------------------------------------------------------------
        Function:         Mary Had A Little Lamb

        Description:      

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Mary_Had_A_Little_Lamb(void)
{
	Delay(60);

	NotePlay(pitch_E5, 1);// e1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_C5, 1);//c1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_E5, 1);//e1
	Delay(50);
	NotePlay(pitch_E5, 1);;//e1
	Delay(50);//delay
	NotePlay(pitch_E5, 2);//e2
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);//delay
	NotePlay(pitch_D5, 2);//d2
	Delay(50);
	NotePlay(pitch_E5, 1);//e1
	Delay(50);
	NotePlay(pitch_G5, 1);//g1
	Delay(50);//delay
	NotePlay(pitch_G5, 1);//g2
	Delay(50);
	NotePlay(pitch_E5, 1);//e1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_C5, 1);//c1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_E5, 1);//e1
	Delay(50);
	NotePlay(pitch_E5, 1);//e1
	Delay(50);//delay
	NotePlay(pitch_E5, 1);//e1
	Delay(50);
	NotePlay(pitch_E5, 1);//e1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_E5, 1);//e1
	Delay(50);
	NotePlay(pitch_D5, 1);//d1
	Delay(50);
	NotePlay(pitch_C5, 4);//c4

}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Twinkle Twinkle Little Star

        Description:      

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Twinkle_Twinkle_Little_Star(void)
{
	Delay(60);

	NotePlay(pitch_C5, 1);
	Delay(30);
	NotePlay(pitch_C5, 1);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_A5, 1);
	Delay(30);
	NotePlay(pitch_A5, 1);
	Delay(30);
	NotePlay(pitch_G5, 2);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_D5, 1);
	Delay(30);
	NotePlay(pitch_D5, 1);
	Delay(30);
	NotePlay(pitch_C5, 2);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_D5, 2);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_D5, 2);
	Delay(30);
	NotePlay(pitch_C5, 1);
	Delay(30);
	NotePlay(pitch_C5, 1);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_G5, 1);
	Delay(30);
	NotePlay(pitch_A5, 1);
	Delay(30);
	NotePlay(pitch_A5, 1);
	Delay(30);
	NotePlay(pitch_G5, 2);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_F5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_E5, 1);
	Delay(30);
	NotePlay(pitch_D5, 1);
	Delay(30);
	NotePlay(pitch_D5, 1);
	Delay(30);
	NotePlay(pitch_C5, 2);



}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Adams Family

        Description:      

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void AdamsFamily(void)
{ //d=4, o=6, b=50
	
	Delay(60);
	
	NotePlay(pitch_P, 1); //32P
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_Gb6, 2); //16f#
	NotePlay(pitch_Bb6, 1); //32a#
	NotePlay(pitch_Gb6, 2); //16f#
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_C6, 2); //16c
	NotePlay(pitch_Ab6, 4); //8g#
	NotePlay(pitch_Gb6, 1); //32f#
	NotePlay(pitch_F6, 2); //16f
	NotePlay(pitch_Ab6, 1); //32g#
	NotePlay(pitch_F6, 2); //16f
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_Bb5, 2); //16a#5
	NotePlay(pitch_Gb6, 4); //8f#
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_Gb6, 2); //16f#
	NotePlay(pitch_Bb6, 1); //32a#
	NotePlay(pitch_Gb6, 2); //16f#
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_C6, 2); //16c
	NotePlay(pitch_Ab6, 4); //8g#
	NotePlay(pitch_Gb6, 1); //32f#
	NotePlay(pitch_F6, 2); //16f
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_Eb6, 2); //16d#
	NotePlay(pitch_F6, 1); //32f
	NotePlay(pitch_Gb6, 8); //f#
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_Eb6, 1); //32d#
	NotePlay(pitch_F6, 1); //32f
	NotePlay(pitch_Gb6, 8); //f#
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_Eb6, 1); //32d#
	NotePlay(pitch_G6, 1); //32g
	NotePlay(pitch_Ab6, 8); //g#
	NotePlay(pitch_Eb6, 1); //32d#
	NotePlay(pitch_F6, 1); //32f
	NotePlay(pitch_G6, 1); //32g
	NotePlay(pitch_Ab6, 2); //16g#.
	NotePlay(pitch_Ab6, 4); //16g#.
	NotePlay(pitch_Eb6, 1); //32d#
	NotePlay(pitch_F6, 1); //32f
	NotePlay(pitch_G6, 1); //32g
	NotePlay(pitch_Ab6, 2); //16g#.
	NotePlay(pitch_Ab6, 4); //16g#.
	NotePlay(pitch_Db6, 1); //32c#
	NotePlay(pitch_Eb6, 1); //32d#
	NotePlay(pitch_F6, 1); //32f
	NotePlay(pitch_Gb6, 1); //32f#
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Beethoven

        Description:      

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void BeethovenPlay(void)
{int a = 0;
	Delay(60);

 while (a < 2)
 {
	NotePlay(pitch_E6, 2);
	NotePlay(pitch_Eb6, 2);
	NotePlay(pitch_E6, 2);
	NotePlay(pitch_Eb6, 2);
	NotePlay(pitch_E6, 2);
	NotePlay(pitch_B5, 2);
	NotePlay(pitch_D6, 2);
	NotePlay(pitch_C6, 2);
	NotePlay(pitch_A5, 4);
	NotePlay(pitch_C5, 2);
	NotePlay(pitch_E6, 2);
	NotePlay(pitch_A6, 2);
	NotePlay(pitch_B6, 4);	
	NotePlay(pitch_E5, 2);
	NotePlay(pitch_A5, 2);
	NotePlay(pitch_B5, 2);
	NotePlay(pitch_C6, 4);

	a++;
	}
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Saregama

        Description:      

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Saregama(void)
{
	Delay(60);

	NotePlay(pitch_Db5, 2);
	NotePlay(pitch_Eb5, 2);
	NotePlay(pitch_F5, 2);
	NotePlay(pitch_Gb5, 2);
	NotePlay(pitch_Ab5, 2);
	NotePlay(pitch_Bb5, 2);
	NotePlay(pitch_C6, 2);
	NotePlay(pitch_Db6, 2);
	NotePlay(pitch_P, 8);
	NotePlay(pitch_Db6, 2);
	NotePlay(pitch_C6, 2);
	NotePlay(pitch_Bb5, 2);
	NotePlay(pitch_Ab5, 2);
	NotePlay(pitch_Gb5, 2);
	NotePlay(pitch_F5, 2);
	NotePlay(pitch_Eb5, 2);
	NotePlay(pitch_Db5, 2);
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Flintstones

        Description:      

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Flintstones(void)
{ 

	Delay(60);

	NotePlay(pitch_Ab5, 2); //g#
	NotePlay(pitch_Db5, 2); //c#
	NotePlay(pitch_P, 1); //8p
	NotePlay(pitch_Db6, 2); //c#6
	NotePlay(pitch_Bb5, 1); //8a#
	NotePlay(pitch_Ab5, 2); //g#
	NotePlay(pitch_Db5, 2); //c#
	NotePlay(pitch_P, 1); //8p
	NotePlay(pitch_Ab5, 2); //g#
	NotePlay(pitch_Gb5, 1); //8f#
	NotePlay(pitch_F5, 1); //8f
	NotePlay(pitch_F5, 1); //8f
	NotePlay(pitch_Gb5, 1); //8f#
	NotePlay(pitch_Ab5, 1); //8g#
	NotePlay(pitch_Db5, 2); //c#
	NotePlay(pitch_Eb5, 2); //d#
	NotePlay(pitch_F5, 4); //2f
	NotePlay(pitch_P, 4); //2p
	NotePlay(pitch_Ab5, 2); //g#
	NotePlay(pitch_Db5, 2); //c#
	NotePlay(pitch_P, 1); //8p
	NotePlay(pitch_Db6, 2); //c#6
	NotePlay(pitch_Bb5, 1); //8a#
	NotePlay(pitch_Ab5, 2); //g#
	NotePlay(pitch_Db5, 2); //c#
	NotePlay(pitch_P, 1); //8p
	NotePlay(pitch_Ab5, 2); //g#
	NotePlay(pitch_Gb5, 1); //8f#
	NotePlay(pitch_F5, 1); //8f
	NotePlay(pitch_F5, 1); //8f
	NotePlay(pitch_Gb5, 1); //8f#
	NotePlay(pitch_Ab5, 1); //8g#
	NotePlay(pitch_Db5, 2); //c#
	NotePlay(pitch_Eb5, 2); //d#
	NotePlay(pitch_Db5, 4); //2c#
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Notes

        Description:      Each of the muscial notes

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void NotePlay(int note, int countTime)
{
	RCAP2L    = note;
	RCAP2H    = note >> 8; // set the frequency for note
	DAC0H = Volume;
	// Play note for countTime length
	NoteCheck();
	Interrupts_Init();
	NoteDelay(countTime*50);
	Interrupts_Off();
	NoteCheck();
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         General_Init

        Description:      Initialise ports, watchdog, timers....

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void General_Init()
{
	WDTCN = 0xde;
	WDTCN = 0xad;
  	SFRPAGE = CONFIG_PAGE;

	P0MDOUT = 0x41;
	XBR0      = 0x04;

	P1MDOUT = 0xf0;
	P2MDOUT = 0xff;
	XBR2 = 0x40;


	Timer_Init();
  	Voltage_Reference_Init();
	DAC_Init();

	SFRPAGE   = TMR4_PAGE;
    TMR4CN    = 0x04;
    TMR4CF    = 0x02;
    RCAP4L    = 0xC6;
    RCAP4H    = 0x06;	// Timer 4 Intial Setting for 2HZ wave (To be changed to 1HZ wave)
    


    SFRPAGE   = TIMER01_PAGE; // UART0 Init
    TCON      = 0x40;
    TMOD      = 0x20;
    CKCON     = 0x10;
    TH1       = 0xF6;

    SFRPAGE   = UART0_PAGE;
    SCON0     = 0x50;








}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Timer_Init

        Description:      Initialise timer 2 ports and registers

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Timer_Init()
{
	SFRPAGE   = TMR2_PAGE;
  	TMR2CN    = 0x04;
  	TMR2CF    = 0x08;
	RCAP2L    = 0x02;
  	RCAP2H    = 0x106;	// 90Hz frequency. Calculated by 1/(1/(24.5MHz/8) x (0xFFFF - 0xBE02)) x 1/2 Hz => Remember two interrupts per cycle
}


/*--------------------------------------------------------------------------------------------------------------------
        Function:         Voltage_Reference_Init

        Description:      Initialise voltage reference for DAC
        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Voltage_Reference_Init()
{
	SFRPAGE   = ADC0_PAGE;
  	REF0CN    = 0x03; // Turn on internal bandgap reference and output buffer to get 2.4V reference (pg 107 of C8051F120 datasheet)
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         DAC_Init

        Description:      Initialise DAC0. 

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void DAC_Init()
{
	SFRPAGE   = DAC0_PAGE;
  	DAC0CN    = 0x9C; // Enable DAC0, data format ""Most" 2nd change" significant orientation, DAC output, Timer 2 overflow
	DAC0L 		= 0x00;
	DAC0H 		= 0x00;
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Interrupts_Init

        Description:      Initialise interrupts

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Interrupts_Init()
{
	IE        = 0xA0;
	
}
/*--------------------------------------------------------------------------------------------------------------------
        Function:         Interrupts_Off

        Description:      Turn off interrupts

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Interrupts_Off()
{
	IE        = 0x00;
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Timer2_ISR

        Description:      Timer 2 interrupt service routine

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Timer2_ISR (void) interrupt 5
{
  unsigned char SFRPAGE_SAVE = SFRPAGE;       // Save Current SFR page

  SFRPAGE   = DAC0_PAGE;
	if (DAC0H == Volume) 												// Toggle DAC output
		DAC0H = 0x00;
	else
		DAC0H = Volume;	

	TF2 = 0;        // Reset Interrupt
  SFRPAGE = SFRPAGE_SAVE; 							      // Restore SFR page
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Timer4_ISR

        Description:      Timer 4 interrupt service routine for playing SSD in play mode

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Timer4_ISR (void) interrupt 16
{
  
  if (count <= 2)
  {
  	count--;
  }
  if (count == 0)
  {
	
  	LetterCheckSSD(j);
	TRIG = 1;
	P2 =  Letter2; // First letter for scrolling in Play 
	LetterCheckSSD(j+1);
	TRIG = 0;
	P2 = Letter2;
	j++;


	
	count = 2;
  }
	TF4 = 0;		
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Delay

        Description:      Delay using timers

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void Delay(unsigned int i)
 
{                       
	 int c=0; // local counter variable

     while(c<i)
     {
	 	
 		
        TMOD=0x01;
        TH0=0xFC;
        TL0=0x66;
        TR0= 1;
        while(!TF0); // var = 1, in ISR make var 0
          TR0=0;
		TF0=0;
		c++;
     }
 
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Note Methods

        Description:      Delay using timers, Note check for buttons

        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
void NoteDelay(unsigned int i)
 
{                       
	 int c=0; // local counter variable

     while(c<i)
     {
        TMOD=0x01;
        TH0=0xFC;
        TL0=0x66;
        TR0= 1;
        while(!TF0); // var = 1, in ISR make var 0
          TR0=0;
		TF0=0;
		c++;
     }
 
}

void NoteCheck()
{
	if(S1 == 0)
	{	
		button_debounce();	// temp button debounce	
		VolumeControl(1); // volume down 
	}
	if(S2 == 0)
	{	
		button_debounce();			
		VolumeControl(0); // volume up 
	}
	if(S3 == 0)
	{	
		button_debounce();	
		State(2); // Pause State 
	}
	if(S4 == 0)
	{		
		button_debounce();		
		State(1); // Stop 
	}
}

/*--------------------------------------------------------------------------------------------------------------------
        Function:         Button_debounce

        Description:      Button debouncer
        Revisions:

--------------------------------------------------------------------------------------------------------------------*/
int button_debounce()
{
	


	buttonCount = (Lock_Input_Time_MSEC / check_msec);	
	
	while ((S1 == 0)&&(buttonCount>0))
	{
		Delay(check_msec);
		buttonCount--;
	}
	buttonCount = Lock_Input_Time_MSEC / check_msec;
	while ((S2 == 0)&&(buttonCount>0))
	{
		Delay(check_msec);
		buttonCount--;
	}
	buttonCount = Lock_Input_Time_MSEC / check_msec;
	while ((S3 == 0)&&(buttonCount>0))
	{
		Delay(check_msec);
		buttonCount--;
	}
	buttonCount = Lock_Input_Time_MSEC / check_msec;
	while ((S4 == 0)&&(buttonCount>0))
	{
		Delay(check_msec);
		buttonCount--;
	}

		
}
// I got a feeling
/*G1,A1,G1,C2,B1,G1,G1,C2,B1,A1,G1,E1,E1,C2,B1,G1,G1,C2,B1,A1,G1,E1,E1,D2,B1,G1,G1,D2,B1,A1,G1,E1,E1,D2,D2,B1,A1,G1,RESTS,0,231,215,211,211,3084,143,313,475,214,249,462,204,300,439,829,178,264,466,241,227,486,198,291,493,846,204,289,468,239,218,472,237,242,460,500,440,238,*/

//Can't get you out of my head
//A1,B1,C2,B1,A1,B1,A1,C2,A1,G1,A1,B1,B1,A1,B1,C2,B1,A1,A1,A1,B1,C2,B1,A1,B1,A1,C2,A1,G1,A1,B1,B1,A1,B1,C2,B1,A1,A1,C2,C2,C2,C2,C2,C2,C2,D2,B1,B1,B1,B1,B1,B1,B1,A1,C2,C2,C2,C2,C2,C2,C2,D2,B1,B1,B1,B1,B1,B1,B1,A1,RESTS,0,573,608,635,413,359,396,477,644,1157,672,593,643,398,381,677,693,408,365,728,621,691,672,382,382,417,443,847,1262,597,608,713,374,404,752,824,407,415,1979,644,527,905,474,516,369,708,716,663,549,932,501,560,381,648,774,621,571,941,525,526,382,635,679,607,595,884,539,559,380,722,

//Itchy and scratchy
//G1,E1,G1,E2,G1,E1,G1,E1,G1,E2,G1,A1,B1,B1,C2,D2,A1,G1,A1,C2,F2,E2,G2,RESTS,0,536,954,573,883,489,417,478,477,560,1288,513,453,919,633,477,1134,454,464,822,609,816,869,


//Impossible by James Arthur
//F2,G2,C2,D#2,D#2,D#2,F2,G2,C2,D#2,D#2,D#2,F2,G2,C2,D#2,D2,C2,D2,F2,G2,C2,D#2,D#2,D#2,F2,G2,C2,D#2,D#2,D#2,F2,G2,C2,D#2,D#2,D#2,F2,G2,C2,D#2,D2,D2,F2,G2,C2,D#2,D#2,D#2,C2,C2,D#2,G2,G2,F2,D#2,D2,C2,C2,D#2,G2,G2,F2,D#2,D2,C2,C2,D#2,G2,F2,D#2,D2,C2,A#1,A#1,D2,F2,D#2,RESTS,0,273,273,273,273,545,545,273,273,273,273,545,545,273,273,273,273,410,136,545,273,273,273,273,545,545,273,273,273,273,545,545,273,273,273,273,545,545,273,273,273,273,545,545,273,273,273,273,545,545,273,273,273,273,410,136,410,136,273,273,273,273,410,136,410,136,273,273,273,273,410,136,410,136,273,273,273,273,2182

//Star Wars
//C1,C1,C1,F1,C2,A#1,A1,G1,F2,C2,A#1,A1,G1,F2,C2,A#1,A1,A#1,G1,C1,C1,C1,F1,C2,A#1,A1,G1,F2,C2,A#1,A1,G1,F2,C2,D#2,D2,D#2,C2,RESTS,0,175,127,278,1168,572,209,197,246,1176,552,201,181,283,1155,580,183,185,236,1784,176,162,275,1162,583,215,180,254,1092,546,219,194,291,1176,581,218,171,235,
