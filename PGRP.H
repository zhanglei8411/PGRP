

	/*====Type Define====*/
	#define UT08	unsigned char
	#define UT8		signed char
	#define UT016 	unsigned short
	#define UT16 	signed short
	#define UT032	unsigned int
	#define UT32	signed int
	#define F32		float
	#define D64		double
	#define L64		long

	/*====Calculation Parameter====*/
	#define 	FAIL				1
	#define 	SUCCESS			0
	#define	OK					0
	#define	FLASE				1

	/*Light Idensity*/
	#define 	SEARCH_RANGE		10
	#define	K_LIGHT_IDENSITY_1	0.05
	#define	K_LIGHT_IDENSITY_2	0.5
	/*Branch off para*/
	#define 	AGE_FOR_BRAN_OFF	8
	#define	BRANCH_OFF_PROB	0.2
	#define	AGE_FOR_BRAN_OFF_K	20
	/*Auxin Function*/
	#define	K_AUXIN_1			1
	#define	K_AUXIN_2			0.1
	#define	K_Grow_1			1
	#define	K_Grow_2			1
	#define	K_Grow_3			(-1.5)
	#define	BEST_AC_FOR_BUD	2
	/*Growing Vector Para*/
	#define	K_Vec_1				2
	#define	K_Vec_2				0.1
	#define	K_Vec_3				0.1
	/*-------*/
	#define	Pi					3.1415926
	#define	BEST_LI_QUANTITY	6
	#define	SMALL_VALUE		0.0001
	#define	MAX_VLAUE			1000000
	#define	GRAVITY				1


	/*====Globle Variable Definition====*/ 
	/*Path Information*/
	#define	NOT_FIND			0
	#define	FIND				1
	#define	MAP_WIDTH			160
	#define	MAP_HEIGHT			120
	#define	MAX_PATH_LENGTH		1000
	#define	MAX_PATH_NUM		5
	/*Map Information*/
	#define 	CELL_IS_BLANK 		0x00
	#define 	CELL_IS_OBSTACLE	0x4f
	#define	CELL_IS_PLANT_BUD	0x42
	#define	CELL_IS_PLANT_STEM 0x42
	#define	CELL_IS_START		0x53
	#define	CELL_IS_TARGET		0x54
	#define	CELL_IS_DEAD_BUD	0x44
	#define	CELL_IS_PATH		0x50
	#define	MAP_PLANT_GROW	"Map.dat"

	/*Plant Information*/
	#define 	MAX_PLANT_CELL_NUM	1000
	#define 	MAX_BUD_NUM			200
	#define	BUD_IS_DEAD			1
	#define	BUD_IS_ALIVE			0


