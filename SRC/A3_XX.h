/*_____________________________________________________________________________________________________________________

        Project:        ELEC2700 Assignment 3 template
        Module:         A3_XX.h
        Author:         Josh Brackenbury and Michael Dobbins
        Date:           05-06-13

        Description:
        This program has been developed to test the functionality of the Speaker

        Revisions:


_______________________________________________________________________________________________________________________*/


//--------------------------------------------------------------------------------------------------------------------
//                              Seven Segment Definitions for Common Anode version
//--------------------------------------------------------------------------------------------------------------------
#define SSOff			0xFF
#define SSZero    0xC0
#define SSOne 		0xF9
#define SSTwo     0xA4
#define SSThree   0xB0
#define SSFour    0x99
#define SSFive    0x92 					
#define SSSix     0x82 					
#define SSSeven   0xF8 					
#define SSEight   0x80 					
#define SSNine    0x98
#define SSA		0x88
#define SSb		0x82
#define SSc    	0xC6
#define SSd 	0xA1
#define SSE     0x86
#define SSF   	0x8E
#define SSG    	0xC2
#define SSh    	0x8b 					
#define SSi     0xFb 					
#define SSJ   	0xE1 					
#define SSK   	0x8A					
#define SSL   	0xC7
#define SSM		0xC8
#define SSn		0xAb
#define SSo		0xA3
#define SSp    	0x8C
#define SSq 	0x84
#define SSr     0xAF
#define SSS   	0x92
#define SSt    	0x87
#define SSu    	0xE3 					
#define SSv     0xC1 					
#define SSW   	0x81 					
#define SSX   	0x89 					
#define SSY   	0x91
#define SSZ		0xE4
				
//--------------------------------------------------------------------------------------------------------------------
//                              Global Variables
//
//	Note: the ^ symbol is used to point to a specific bit. For more information refer to the Keil compiler manual
//--------------------------------------------------------------------------------------------------------------------
sbit TRIG = P0 ^ 6;                         // Name Port0.6 for SSD1 and SSD2 display   

sbit S1 = P1 ^ 0;                           // Pushbutton S1
sbit S2 = P1 ^ 1;                           // Pushbutton S2
sbit S3 = P1 ^ 2;                           // Pushbutton S3   
sbit S4 = P1 ^ 3;                           // Pushbuttom S4

sbit LED7 = P1 ^ 4;                         // LED7   
sbit LED8 = P1 ^ 5;                         // LED8
sbit LED9 = P1 ^ 6;                         // LED9
sbit LED10 = P1 ^ 7;                        // LED10   


sbit P3_7 = P3 ^ 7;

// Global variables for debounce button
#define check_msec	1	// Read hardware every 3 msec
#define Press_MSEC	10	// Stable time before registering pressed
#define Lock_Input_Time_MSEC	50	// Stable time before registering released
int buttonCount = Lock_Input_Time_MSEC; // check_msec


#define pitch_P		0
#define pitch_C5	64580
#define pitch_Db5	64634
#define pitch_D5	64685
#define pitch_Eb5	64732
#define pitch_E5	64778
#define pitch_F5	64820
#define pitch_Gb5	64860
#define pitch_G5	64898
#define pitch_Ab5	64934
#define pitch_A5	64968
#define pitch_Bb5	65000
#define pitch_B5	65030
#define pitch_C6	65058
#define pitch_Db6	65085
#define pitch_D6	65110
#define pitch_Eb6	65134
#define pitch_E6	65157
#define pitch_F6	65178
#define pitch_Gb6	65198
#define pitch_G6	65217
#define pitch_Ab6	65235
#define pitch_A6	65252
#define pitch_Bb6	65268
#define pitch_B6	65283

#define MelodyPin	P3_7


unsigned char Volume;									// Global variable for volume level
int volumeSelect = 4;										// Global variable for volume selection
int selection = 0;											//Global variable for song selection
int Letter1 = 0xFF;											// Global variables to display SSD
int	Letter2 = 0xFF;											// Global variables to display SSD
int arrayLengthnum = 20;									// Intial variable to define the length of Array
int j = 0; //array variable	
int count = 2; //SSD 1HZ countdown
char str[30] = "Mary Had A Little Lamb" ;					//  Array used to display SSD						
int counter = 0;
int arraySize = 198;										//Array size used for upload song file  length
	

//--------------------------------------------------------------------------------------------------------------------
//                              Function prototypes
//--------------------------------------------------------------------------------------------------------------------
void main(void);
void General_Init(void);
void Timer_Init(void);
void Voltage_Reference_Init(void);
void DAC_Init(void);
void Interrupts_Init(void);
void Interrupts_Off(void);
void Mary_Had_A_Little_Lamb(void);
void Twinkle_Twinkle_Little_Star(void);
void AdamsFamily(void);
void BeethovenPlay(void);
void Saregama(void);
void Flintstones(void);
void NoteCheck(void);
void NotePlay(int note,int countTime);
void Delay(unsigned int i);
void NoteDelay(unsigned int i);
void State(int i);
void Play(void);
void Stop(void);
void Pause(void);
int RandomNum(void);
void VolumeControl(int updown);
void Computer_Interface(void);
void UARTInit();
void SongMenu(void);
void LetterCheckSSD(int j);
void PlayInit(void);
int button_debounce(void);
void UploadSong(void);
void DownloadSong(void);
void PlayUpload(char a[]);
void Download(int a);
void Keyboard(void);
void KeyboardPlay(int a);

