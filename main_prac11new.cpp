//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0, rotRodDer = 0, rotBraizq = 0, rotBraDer = 0;
float giroMonito = 0;

#define MAX_FRAMES 10
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodDer;
	float rotinc2;
	float rotRodIzq;
	float rotInc;
	float rotBraIzq1;
	float rotBraDer2;
	float rotInc3;
	float rotInc4;
	float giroMonito;
	float giroMonitoInc;
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01


//NEW///////////////////////////7

CTexture textMesa;
CTexture textPata;
CTexture textWall;
CTexture textSilla;
CTexture textTecho;
CTexture textMarble;
CTexture textPiso;
CTexture textGlassWasser;
CTexture textBarrote;
CTexture textCuadro1;
CTexture textMarco;
CTexture textLibroCG;
CTexture textPB;
CTexture textPuerta;
CTexture textPuerta_princ;
CTexture textMarco_1;
CTexture textMarco_2;
CTexture textMarco_3;
CTexture textGrass;
CTexture textSky;
CTexture textLibrero;

//***ROSE****
CTexture textAlmohada;
CTexture textColcha;
CTexture textMaderaBuro;
CTexture textMaderaCama;
CTexture textLampara;
CTexture textLaptop;
CTexture textPantalla;
CTexture textTeclado;
CTexture textTouchPad;
CTexture textGW;

//CFiguras fig1;
//CFiguras fig5;
CFiguras tablaMesa;
CFiguras pata1Mesa;
CFiguras pata2Mesa;
CFiguras pata3Mesa;
CFiguras pata4Mesa;
CFiguras asientoSilla;
CFiguras respaldoSilla1;
CFiguras respaldoSilla2;
CFiguras respaldoSilla3;
CFiguras respaldoSilla4;
CFiguras techoCasa;
CFiguras pisoCasa;
CFiguras cubo;
CFiguras sky;
CFiguras tarja;
CFiguras asiento;
//*****ROSE*****

CFiguras cama;
CFiguras buro;
CFiguras cono;
CFiguras lampara;
CFiguras laptop;

///////CasaBob

CTexture textSillas;
CTexture textEstufa;
CTexture textRepisa;
CTexture textBarril;
CTexture textMesa1;
CTexture textTablaMesa;
CTexture textRefri;
CTexture textChimenea;
CTexture textArena;
CTexture textCubeta;
CTexture textSurf;
CTexture textTablon1;
CTexture textTablon;
CTexture textParrilla;
CTexture textPiña;
CTexture textPuertab;
CTexture textVentanab;
CTexture textPiña2;
CTexture textMetalb;
CTexture textAzul;
CFiguras Piña2;

///////////


float abrirPuerta = 0;
//END NEW//////////////////////////////////////////

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito
CFiguras fig8; 


void saveFrame ( void )
{
	
	printf("frameindex %d\n",FrameIndex);			

	KeyFrame[FrameIndex].posX=posX;
	KeyFrame[FrameIndex].posY=posY;
	KeyFrame[FrameIndex].posZ=posZ;

	KeyFrame[FrameIndex].rotRodIzq=rotRodIzq;
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].rotBraIzq1 = rotBraizq;
	KeyFrame[FrameIndex].rotBraDer2 = rotBraDer;
	KeyFrame[FrameIndex].giroMonito=giroMonito;
			
	FrameIndex++;
}

void resetElements( void )
{
	posX=KeyFrame[0].posX;
	posY=KeyFrame[0].posY;
	posZ=KeyFrame[0].posZ;

	rotRodIzq=KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;
	rotBraizq = KeyFrame[0].rotBraIzq1;
	rotBraDer = KeyFrame[0].rotBraDer2;
	giroMonito=KeyFrame[0].giroMonito;

}

void interpolation ( void )
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;	
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;	
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;	

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;	
	KeyFrame[playIndex].rotinc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBraIzq1 - KeyFrame[playIndex].rotBraIzq1) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotBraDer2 - KeyFrame[playIndex].rotBraDer2) / i_max_steps;

	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}


void ciudad ()
{

		glPushMatrix(); //Camino1
			glTranslatef(23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino2
			glTranslatef(-23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,-4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,7.0);
			glRotatef(90,1,0,0);
			glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,-7.0);
			glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		fig7.prisma(2.0 ,2.0 ,1 ,text2.GLindex);

		glPushMatrix();//Cuello
			glTranslatef(0, 1.0, 0.0);
			fig7.cilindro(0.25, 0.25, 15, 0);
			glPushMatrix();//Cabeza
				glTranslatef(0, 1.0, 0);
				fig7.esfera(0.75, 15, 15, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
			glTranslatef(1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(0.25, 0, 0);
				glRotatef(-45+rotBraDer, 0, 1, 0); 
				glRotatef(25, 0, 0, 1);
				glRotatef(25, 1, 0, 0);
				glTranslatef(0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
			glTranslatef(-1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(-0.25, 0, 0);
				glRotatef(45+rotBraizq, 0, 1, 0); 
				glRotatef(25, 0, 0, 1);
				glRotatef(25, 1, 0, 0); 
				glTranslatef(-0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
			glColor3f(0, 0, 1);
			glTranslatef(0, -1.5, 0);
			fig7.prisma(1, 2, 1, 0);

			glPushMatrix(); //Pie Derecho -->
				glTranslatef(0.75, -0.5, 0);
				glRotatef(-15, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodDer, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


			glPushMatrix(); //Pie Izquierdo -->
				glTranslatef(-0.75, -1.5, 0);
				glRotatef(-5, 1, 0, 0);
				glTranslatef(0, -1.0, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.25, 0);
					glRotatef(15+rotRodIzq, 1, 0, 0);
					glTranslatef(0, -1.0, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.5, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}



//NEW CASA//////////////////////////////////////





void mesa(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosMesa, GLfloat yPosMesa, GLfloat zPosMesa) {
	//mesa	
		//tabla
	glPushMatrix();
	glScalef(xMadera, yMadera, zMadera);
	glTranslatef(xPosMesa, yPosMesa, zPosMesa);
	glPushMatrix();
	glScalef(10, .5, 5);
	tablaMesa.prisma(1.0, 1.0, 1.0, textTablaMesa.GLindex);
	//patas
	glPopMatrix();
	glPushMatrix();
	

	glTranslatef(0.0, -2.75, 0.0);
	glScalef(3.0, 5.0, 3.0);
	pata2Mesa.torus(1.0, 0.1, 15.0, 15.0, textMesa.GLindex);



	glPopMatrix();
	glPopMatrix();

	return;
}


void estufilla(void) {

	glPushMatrix();
	glTranslatef(0, 0, 0);
	fig8.cilindro(1.0, 1.0, 20, textEstufa.GLindex);//////Estufa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1, 0.6);
	fig8.cilindro(0.3, 0.05, 10, textParrilla.GLindex);//////Parrilla1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 1, -0.5);
	fig8.cilindro(0.3, 0.05, 10, textParrilla.GLindex);//////Parrilla2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 1, -0.5);
	fig8.cilindro(0.3, 0.05, 10, textParrilla.GLindex);//////Parrilla3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 1, 0.5);
	glRotatef(5.0, 1.0, 0.0, 0.0);
	fig8.cilindro(0.1, 1.0, 10, textChimenea.GLindex);//////Chimenea1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 2, 0.6);
	glRotatef(-5.0, 1.0, 0.0, 0.0);
	fig8.cilindro(0.1, 1.0, 10, textChimenea.GLindex);//////chimenea2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 3, 0.5);
	glRotatef(-5.0, 1.0, 0.0, 0.0);
	fig8.cilindro(0.1, 1.0, 10, textChimenea.GLindex);//////Chimenea3
	glPopMatrix();


	///////ventana
	glPushMatrix();
	glTranslatef(0, 0.5, -0.9999);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	//glRotatef(90.0, 0.0, 1.0, 0.0);
	cubo.prisma(0.8, 0.8, 0.01, textVentanab.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	return;
}







void silla(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosSilla, GLfloat yPosSilla, GLfloat zPosSilla) {
	//float numBarrotes = -2.9;
	glPushMatrix();
	//posicion y tamaño
	glScalef(xMadera, yMadera, zMadera);
	glTranslatef(xPosSilla, yPosSilla, zPosSilla);
	//figura
	glPushMatrix();
		glScalef(3, .5, 3);
		asientoSilla.prisma(1.0, 1.0, 1.0, textSillas.GLindex);//1
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.35, -3.25, -1.35);
		glScalef(.3, 6, .3);
		pata1Mesa.prisma(1.0, 1.0, 1.0, textSillas.GLindex);
		glTranslatef(-9.0, 0, 0);
		pata2Mesa.prisma(1.0, 1.0, 1.0, textSillas.GLindex);
		glTranslatef(0, 0, 9);
		pata3Mesa.prisma(1.0, 1.0, 1.0, textSillas.GLindex);
		glTranslatef(9, 0, 0);
		pata4Mesa.prisma(1.0, 1.0, 1.0, textSillas.GLindex);
	glPopMatrix();

	//glPushMatrix();
	//	glTranslatef(1.0, 2.25, -1.45);
	//	glScalef(0.5, 4.0, 0.1);
	//	respaldoSilla1.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
	//	glTranslatef(-1.0, 0.5, 0.0);
	//	glScalef(0.5, 2.0, 1.0);
	//	respaldoSilla1.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
	//	glTranslatef(-1.0, -0.25, 0.0);
	//	glScalef(0.5, 0.5, 1.0);
	//	respaldoSilla1.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 2.25, -1.45);
	glScalef(0.2, 4.0, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, 2.5, -1.45);
	glScalef(0.2, 4.5, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, 2.75, -1.45);
	glScalef(0.2, 5.0, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 2.75, -1.45);
	glScalef(0.2, 5.0, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P4
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 2.5, -1.45);
	glScalef(0.2, 4.5, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P5
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 2.25, -1.45);
	glScalef(0.2, 4.0, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P6
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 2.5, -1.45);
	glScalef(0.2, 4.5, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P7
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 2.75, -1.45);
	glScalef(0.2, 5.0, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P8
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.6, 2.75, -1.45);
	glScalef(0.2, 5.0, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P9
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8, 2.5, -1.45);
	glScalef(0.2, 4.5, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P10
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 2.25, -1.45);
	glScalef(0.2, 4.0, 0.1);
	respaldoSilla1.prisma(1, 1, 1, textSillas.GLindex);///////P11
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, 0.5, -1.45);
	glScalef(0.3, 0.3, 0.3);
	respaldoSilla1.esfera(1, 15, 15, textSillas.GLindex);//////EsferaREspaldo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.2, 0.5, -1.45);
	glScalef(0.3, 0.3, 0.3);
	respaldoSilla1.esfera(1, 15, 15, textSillas.GLindex);//////EsferaREspaldo
	glPopMatrix();
	
	glPopMatrix();

	return;
}



void comedor(void){
	glPushMatrix();
			mesa(2,2,2,0,0,0);
	glPopMatrix();


	//SILLAS
	glPushMatrix();
		glTranslatef(0,0,-0.5);
		glRotatef(25, 0,1,0);
		glTranslatef(2,0,-0.5);
		silla(1, 1.0, 1, 5, -3, -6.5);
	glPopMatrix();


	glPushMatrix();
			glRotatef(180.0, 0.0, 1.0, 0.0);
			silla(1, 1.0, 1, 5, -3, -7.50);
	glPopMatrix();
		

	glPushMatrix();
			//silla(1,1,1,2,-1,-6.5);
	glPopMatrix();

	
		return;
}



void refrigerador(void) {
	glPushMatrix();
	glTranslatef(4, -30, 50.5);
	fig5.prisma(30.0, 1.0, 15.0, textRefri.GLindex);//////PuertaRefri1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, -5, 50.5);
	fig5.prisma(20.0, 1.0, 15.0, textRefri.GLindex);//////PuertaRefri2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, -20, 50);
	fig5.prisma(50.0, 1.0, 15.0, textRefri.GLindex);//////FrenteRefri
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, -20, 42.5);///////Derecharefri
	glRotatef(90, 1, 0, 0);
	fig5.prisma(1.0, 13.0, 50.0, textRefri.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, -20, 57.5);
	glRotatef(90, 1, 0, 0);
	fig5.prisma(1.0, 13.0, 50.0, textRefri.GLindex);///////////IzquierdaRefri
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-3.0, -45, 50);
	fig5.prisma(0.5, 13.0, 16.0, textRefri.GLindex);///////AbajoRefri
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.0, 5, 50);
	fig5.prisma(0.5, 13.0, 16.0, textRefri.GLindex);////////ArribaRefri
	glPopMatrix();

	///////ventana
	glPushMatrix();
	glTranslatef(4.1, -5, 50);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	cubo.prisma(10, 10, 1, textVentanab.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(4.8, -5, 57);
	fig5.prisma(4.5, 0.5, 0.5, textMetalb.GLindex);///////soporte1

	glTranslatef(0.0, -20, 0.0);
	fig5.prisma(4.5, 0.5, 0.5, textMetalb.GLindex);///////soporte2
	glPopMatrix();




}


void cubeta(void) {

	glPushMatrix();
	glScalef(1, 1, 1);
	glTranslatef(10, 0, 10);
	tarja.cilindro(1.0, 3.0, 20, textArena.GLindex);
	glTranslatef(0, 3.0, 0);
	tarja.cilindro(1.5, 3.5, 20, textCubeta.GLindex);
	glPopMatrix();
	return;
}


void barril(void) {

	glPushMatrix();
	glScalef(1, 1, 1);
	glTranslatef(1, 1, 1);
	asiento.cilindro(1.0, 4.0, 15, textBarril.GLindex);
	glPopMatrix();
	return;
}


//////////////////////CasaBob

void casa(void) {
	//*****casa*****
	glPushMatrix(); //Creamos paredes (izquierda, derecha, atras)
	glTranslatef(0, 40, 0);
	fig1.skybox2(100.0, 50.0, 50.0, textPiña.GLindex);//////(izquierda, derecha, atras)
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 90, 0);
	techoCasa.prisma(1, 50, 50, textPiña.GLindex);///////Techo
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(0, -10, 0);
	pisoCasa.prisma(1, 85, 85, textArena.GLindex);/////Piso
	//patio
	glTranslatef(0, -3, 0);
	//pisoCasa.prisma(1,250,250, textGrass.GLindex);
	glPopMatrix();


	glPushMatrix();/////////frente dividido
	glTranslatef(-14.9, 40, -24.5);
	pisoCasa.prisma(100, 20, 1, textPiña.GLindex);/////paredfrente
	glTranslatef(29.8, 0, 0);
	pisoCasa.prisma(100, 20, 1, textPiña.GLindex);/////paredfrente
	glTranslatef(-15, 19, 0);
	pisoCasa.prisma(62.9, 10, 1, textPiña.GLindex);/////paredfrente
	
	glTranslatef(15, -1, 0);
	glRotatef(abrirPuerta, 0, 1, 0);
	glTranslatef(-15, -49, 0);//eran 20 en x
	pisoCasa.prisma(37, 9.9, 1, textPuertab.GLindex);/////puerta
	glPopMatrix();



	//ventana 1
	glPushMatrix();
	glTranslatef(-15, 30, -24.3);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	cubo.prisma(20, 15, 1.5, textVentanab.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//ventana 2
	glPushMatrix();
	glTranslatef(15, 50, -24.3);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	cubo.prisma(20, 15, 1.5, textVentanab.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25.2,60,-20);
	glRotatef(90,0,0,1);
	fig8.cilindro(1.0,8,15,textChimenea.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-33, 65, -20);
	glRotatef(180, 1, 0, 0);
	fig8.cono(5.0, 2.5, 15, textChimenea.GLindex);
	glPopMatrix();



	///////Planta
	glPushMatrix();
	glTranslatef(0, 120, -5);
	//glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	Piña2.prisma(60, 60, 0.01, textPiña2.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	///////Planta
	glPushMatrix();
	glTranslatef(0, 120, -5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	Piña2.prisma(60, 60, 0.01, textPiña2.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	return;
}

///////////////////////7



void repisa(void) {
	glPushMatrix();
	glTranslatef(-19, 30, 37);
	glRotatef(90, 1.0, 0.0, 0.0);
	cubo.prisma(10, 10, 0.3, textRepisa.GLindex);////////Repisa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13.75, 34.3, 40);
	glRotatef(25.0, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	cubo.prisma(0.5, 10.0, 0.5, textTeclado.GLindex);////////soporte
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.25, 34.3, 40);
	glRotatef(25.0, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	cubo.prisma(0.5, 10.0, 0.5, textTeclado.GLindex);////////soporte
	glPopMatrix();


	return;
}



void mesaSurf(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosBuro, GLfloat yPosBuro, GLfloat zPosBuro)
{
	glPushMatrix();
	glScalef(xMadera, yMadera, zMadera);
	glTranslatef(xPosBuro, yPosBuro, zPosBuro); //figura 
	//contorno
	glPushMatrix();
	glTranslatef(1.5, 5.5, 1.5);
	glScalef(1.0, 11.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon1.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 5.5, 8.5);
	glScalef(1.0, 11.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon1.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14.5, 5.5, 1.5);
	glScalef(1.0, 11.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon1.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14.5, 5.5, 8.5);
	glScalef(1.0, 11.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon1.GLindex);
	glPopMatrix();


	//rellenos
	glPushMatrix();
	glTranslatef(13.5, 6.0, 5.0);
	glScalef(1.0, 10, 6.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 6.0, 5.0);
	glScalef(1.0, 10, 6.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon.GLindex);
	glPopMatrix();

	//pared atras
	glPushMatrix();
	glTranslatef(8.0, 6.0, 1.5);
	glScalef(12.0, 10, 1.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon.GLindex);
	glPopMatrix();


	//pared frente
	glPushMatrix();
	glTranslatef(8.0, 6.0, 8.5);
	glScalef(12.0, 10, 1.0);
	buro.prisma(1.0, 1.0, 1.0, textTablon.GLindex);
	glPopMatrix();


	//base arriba
	glPushMatrix();
	glTranslatef(8.0, 11.5, 5.0);
	glScalef(16.0, 1.0, 10.0);
	buro.prisma(1.0, 1.0, 1.0, textSurf.GLindex);
	glPopMatrix();

	//base arriba
	glPushMatrix();
	glTranslatef(3.5, 13.5, 5.0);
	//glScalef(16.0, 1.0, 10.0);
	buro.prisma(2.5, 2.0, 0.5, textAzul.GLindex);
	glPopMatrix();





	
}



//END CASA////////////////////////////////////





GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("Casa/logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();


	//NEW////////////////////////////////////////////

	textMesa.LoadBMP("casa/wood_5.bmp");
	textMesa.BuildGLTexture();
	textMesa.ReleaseImage();

	textPata.LoadBMP("casa/brick_3.bmp");
	textPata.BuildGLTexture();
	textPata.ReleaseImage();

	textWall.LoadBMP("casa/brick_2.bmp");
	textWall.BuildGLTexture();
	textWall.ReleaseImage();

	textSilla.LoadBMP("casa/madera.bmp");
	textSilla.BuildGLTexture();
	textSilla.ReleaseImage();
	
	textTecho.LoadBMP("casa/brick_3.bmp");
	textTecho.BuildGLTexture();
	textTecho.ReleaseImage();

	textMarble.LoadBMP("casa/marble_2.bmp");
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	textPiso.LoadBMP("casa/floor-parquet.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textGlassWasser.LoadBMP("casa/glass_2.bmp");
	textGlassWasser.BuildGLTexture();
	textGlassWasser.ReleaseImage();

	textBarrote.LoadBMP("casa/brickwall.bmp");
	textBarrote.BuildGLTexture();
	textBarrote.ReleaseImage();

	textCuadro1.LoadBMP("casa/repisa_1.bmp");
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();

	textMarco.LoadBMP("casa/burned wood.bmp");
	textMarco.BuildGLTexture();
	textMarco.ReleaseImage();

	textLibroCG.LoadBMP("casa/gc_donald.bmp");
	textLibroCG.BuildGLTexture();
	textLibroCG.ReleaseImage();

	textPuerta.LoadBMP("casa/door_3.bmp");
	textPuerta.BuildGLTexture();
	textPuerta.ReleaseImage();

	textPuerta_princ.LoadBMP("casa/door_3_4_puerta.bmp");
	textPuerta_princ.BuildGLTexture();
	textPuerta_princ.ReleaseImage();

	textMarco_1.LoadBMP("casa/door_3_1_izq.bmp");
	textMarco_1.BuildGLTexture();
	textMarco_1.ReleaseImage();

	textMarco_2.LoadBMP("casa/door_3_2_der.bmp");
	textMarco_2.BuildGLTexture();
	textMarco_2.ReleaseImage();

	textMarco_3.LoadBMP("casa/door_3_3_cen.bmp");
	textMarco_3.BuildGLTexture();
	textMarco_3.ReleaseImage();

	textGrass.LoadBMP("casa/grass_2.bmp");
	textGrass.BuildGLTexture();
	textGrass.ReleaseImage();

	textSky.LoadTGA("texturas/sky.tga");
	textSky.BuildGLTexture();
	textSky.ReleaseImage();

	textLibrero.LoadBMP("casa/strata.bmp");
	textLibrero.BuildGLTexture();
	textLibrero.ReleaseImage();

	textGW.LoadBMP("casa/glass window.bmp");
	textGW.BuildGLTexture();
	textGW.ReleaseImage();
	
	//*****ROSE******
	textAlmohada.LoadBMP("casa/almohada.bmp");
	textAlmohada.BuildGLTexture();
	textAlmohada.ReleaseImage();

	textColcha.LoadBMP("casa/colcha.bmp");
	textColcha.BuildGLTexture();
	textColcha.ReleaseImage();

	textMaderaBuro.LoadBMP("casa/buro.bmp");
	textMaderaBuro.BuildGLTexture();
	textMaderaBuro.ReleaseImage();

	textMaderaCama.LoadBMP("casa/maderaCama.bmp");
	textMaderaCama.BuildGLTexture();
	textMaderaCama.ReleaseImage();

	textLampara.LoadBMP("casa/lampara.bmp");
	textLampara.BuildGLTexture();
	textLampara.ReleaseImage();

	textLaptop.LoadBMP("casa/laptop.bmp");
	textLaptop.BuildGLTexture();
	textLaptop.ReleaseImage();

	textPantalla.LoadBMP("casa/windows.bmp");
	textPantalla.BuildGLTexture();
	textPantalla.ReleaseImage();

	textTeclado.LoadBMP("casa/tecla.bmp");
	textTeclado.BuildGLTexture();
	textTeclado.ReleaseImage();

	textTouchPad.LoadBMP("casa/touchpad.bmp");
	textTouchPad.BuildGLTexture();
	textTouchPad.ReleaseImage();

	/////////CasaBob

	textSillas.LoadTGA("texturas/sillas.tga");
	textSillas.BuildGLTexture();
	textSillas.ReleaseImage();

	textEstufa.LoadTGA("texturas/Estufa.tga");
	textEstufa.BuildGLTexture();
	textEstufa.ReleaseImage();

	textRepisa.LoadTGA("texturas/repisa.tga");
	textRepisa.BuildGLTexture();
	textRepisa.ReleaseImage();

	textBarril.LoadTGA("texturas/barril.tga");
	textBarril.BuildGLTexture();
	textBarril.ReleaseImage();

	textMesa.LoadTGA("texturas/pelota.tga");
	textMesa.BuildGLTexture();
	textMesa.ReleaseImage();

	textTablaMesa.LoadTGA("texturas/mesa.tga");
	textTablaMesa.BuildGLTexture();
	textTablaMesa.ReleaseImage();

	textRefri.LoadTGA("texturas/Refri.tga");
	textRefri.BuildGLTexture();
	textRefri.ReleaseImage();

	textChimenea.LoadTGA("texturas/chimenea.tga");
	textChimenea.BuildGLTexture();
	textChimenea.ReleaseImage();

	textArena.LoadTGA("texturas/arena.tga");
	textArena.BuildGLTexture();
	textArena.ReleaseImage();

	textCubeta.LoadTGA("texturas/cubeta.tga");
	textCubeta.BuildGLTexture();
	textCubeta.ReleaseImage();

	textSurf.LoadTGA("texturas/surf.tga");
	textSurf.BuildGLTexture();
	textSurf.ReleaseImage();

	textTablon.LoadTGA("texturas/tablon.tga");
	textTablon.BuildGLTexture();
	textTablon.ReleaseImage();

	textTablon1.LoadTGA("texturas/tablon1.tga");
	textTablon1.BuildGLTexture();
	textTablon1.ReleaseImage();

	textParrilla.LoadTGA("texturas/parrilla.tga");
	textParrilla.BuildGLTexture();
	textParrilla.ReleaseImage();

	textPiña.LoadTGA("texturas/pared.tga");
	textPiña.BuildGLTexture();
	textPiña.ReleaseImage();

	textPuertab.LoadTGA("texturas/puerta.tga");
	textPuertab.BuildGLTexture();
	textPuertab.ReleaseImage();

	textVentanab.LoadTGA("texturas/ventana.tga");
	textVentanab.BuildGLTexture();
	textVentanab.ReleaseImage();

	textPiña2.LoadTGA("texturas/piña2.tga");
	textPiña2.BuildGLTexture();
	textPiña2.ReleaseImage();

	textMetalb.LoadTGA("texturas/metalb.tga");
	textMetalb.BuildGLTexture();
	textMetalb.ReleaseImage();

	textAzul.LoadTGA("texturas/tazul.tga");
	textAzul.BuildGLTexture();
	textAzul.ReleaseImage();


	//////////


	//END NEW//////////////////////////////

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotRodDer = 0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].rotinc2 = 0;
		KeyFrame[i].rotBraIzq1 = 0;
		KeyFrame[i].rotBraDer2 = 0;
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].rotInc4 = 0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

	//carga las posiciones que se imprimieron en el elemento del 
	// arreglo de estructuras anim1
	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = 1.5;
	KeyFrame[0].rotRodIzq = 45;
	KeyFrame[0].rotRodDer = -45;
	FrameIndex++;

	KeyFrame[1].posX = 15;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = 1.5;
	KeyFrame[1].giroMonito = 90;
	KeyFrame[1].rotRodIzq = 0;
	KeyFrame[1].rotRodDer = 0;
	FrameIndex++;

	KeyFrame[2].posX = 30;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = 1.5;
	KeyFrame[2].giroMonito = 180;
	KeyFrame[2].rotRodIzq = 45;
	KeyFrame[2].rotRodDer = -45;
	FrameIndex++;

	// arreglo de estructuras anim2 moonWalker

	KeyFrame[3].posX = 30;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = 1.5;
	KeyFrame[3].giroMonito = 180;
	KeyFrame[3].rotRodIzq = 45;
	KeyFrame[3].rotRodDer = -45;
	FrameIndex++;

	KeyFrame[4].posX = 30;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = 0;
	KeyFrame[4].giroMonito = 90;
	KeyFrame[4].rotRodIzq = 0;
	KeyFrame[4].rotRodDer = 0;
	FrameIndex++;

	KeyFrame[5].posX = 30;
	KeyFrame[5].posY = 2.5;
	KeyFrame[5].posZ = -1.5;
	KeyFrame[5].giroMonito = 0;
	KeyFrame[5].rotRodIzq = 45;
	KeyFrame[5].rotRodDer = -45;
	FrameIndex++;

	// arreglo de estructuras anim3
	
	KeyFrame[6].posX = 30;
	KeyFrame[6].posY = 2.5;
	KeyFrame[6].posZ = -1.5;
	KeyFrame[6].giroMonito = 0;
	KeyFrame[6].rotRodIzq = 45;
	KeyFrame[6].rotRodDer = -45;
	FrameIndex++;

	KeyFrame[7].rotBraIzq1 = 60;
	KeyFrame[7].rotBraDer2 = 60;
	KeyFrame[7].posX = 30;
	KeyFrame[7].posY = 2.5;
	KeyFrame[7].posZ = -1.5;
	KeyFrame[7].giroMonito = 0;
	KeyFrame[7].rotRodIzq = 45;
	KeyFrame[7].rotRodDer = -45;
	FrameIndex++;

	KeyFrame[8].rotBraIzq1 = 0;
	KeyFrame[8].rotBraDer2 = 0;
	KeyFrame[8].posX = 30;
	KeyFrame[8].posY = 2.5;
	KeyFrame[8].posZ = -1.5;
	KeyFrame[8].giroMonito = 0;
	KeyFrame[8].rotRodIzq = 45;
	KeyFrame[8].rotRodDer = -45;
	FrameIndex++;

	KeyFrame[9].rotBraIzq1 = -60;
	KeyFrame[9].rotBraDer2 = -60;
	KeyFrame[9].posX = 30;
	KeyFrame[9].posY = 2.5;
	KeyFrame[9].posZ = -1.5;
	KeyFrame[9].giroMonito = 0;
	KeyFrame[9].rotRodIzq = 45;
	KeyFrame[9].rotRodDer = -45;
	FrameIndex++;

	//

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
	

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,textSky.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					//glScalef(0.5, 0.5, 0.5);
					//monito();
					glCallList(ciudad_display_list);
					glTranslatef(posX, posY, posZ);
					glRotatef(giroMonito, 0, 1, 0);
					monito();
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();			

			glPushMatrix(); //Flecha
				glScalef(7,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma_anun(text3.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();


			//CASA///////////////////
			//¨****casa*****
			glPushMatrix();
				glScalef(1.0, 0.5, 1.0);
				glTranslatef(30, 3, -17.2);
				glRotatef(180, 0, 1, 0);
				glDisable(GL_LIGHTING);
				glScalef(0.3, 0.3, 0.3);
					casa();
				
				glPushMatrix();

					//****COMEDOR***
					glPushMatrix();
						glTranslatef(10,2.5,-5);
						glScalef(1.3,1.3,1.3);
						comedor();
					glPopMatrix();
					
				
					

					
					//*****ROSE*****
					glPushMatrix(); 
						glPushMatrix();
							glTranslatef(0,0,-0.5); 
							glRotatef(90, 0,1,0); 
							glTranslatef(2,0,-0.5);
						//	dibujaCama(1.1,1.1,1.1,14.0,-5.5,-37.0); 
						glPopMatrix();
						glPushMatrix();
							glRotatef(90, 0,1,0); 
							mesaSurf(1,1,1,5,-9.5,-24.0); 
						glPopMatrix();
						
					glPopMatrix();
					//******JOAN*****
					//refrigerador
					glPushMatrix();
						glRotatef(90, 0,1,0);
						glTranslatef(-17,23,-35);
						glScalef(.7,.7,.7);
						refrigerador();
					glPopMatrix();

					/////estufa
					glPushMatrix();
					glTranslatef(-15, -8, 15);
					glScalef(6.0, 9.0, 6.0);
					estufilla();
					glPopMatrix();


					//////tarja
					glPushMatrix();
					glTranslatef(-42, -9, -15);
					glScalef(2.0, 2.0, 2.0);
					cubeta();
					glPopMatrix();


					////////Barril
					glPushMatrix();
					glTranslatef(-23, 22, 3);
					glScalef(3, 3, 3);
					barril();
					glPopMatrix();

					/////////Repisa
					glPushMatrix();
					glRotatef(-90.0, 0.0, 1.0, 0.0);
					glTranslatef(25, -5, -17.5);
					repisa();
					glPopMatrix();

				glPopMatrix();

			glEnable(GL_LIGHTING);
			glPopMatrix();
					

			glColor3f(1.0,1.0,1.0);

		glPopMatrix();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto Final");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	//Movimiento del monito
	if(play)
	{		
		
		if(	i_curr_steps >= i_max_steps) //end of animation between frames?
		{			
			playIndex++;		
			if(playIndex>FrameIndex-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex=0;
				play=false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX+=KeyFrame[playIndex].incX;
			posY+=KeyFrame[playIndex].incY;
			posZ+=KeyFrame[playIndex].incZ;

			rotRodIzq+=KeyFrame[playIndex].rotInc;
			rotRodDer += KeyFrame[playIndex].rotinc2;
			rotBraizq += KeyFrame[playIndex].rotInc3;
			rotBraDer += KeyFrame[playIndex].rotInc4;
			giroMonito+=KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}
		
	}


	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			printf("%f \n", rotRodIzq);
			break;

		case 'u':
			rotRodDer++;
			break;

		case 'U':
			rotRodDer--;
			break;

		case 'n':
			rotBraizq++;
			break;

		case 'N':
			rotBraizq--;
			break;

		case 'm':
			rotBraDer++;
			break;

		case 'M':
			rotBraDer--;
			break;

		case 'p':						
			giroMonito++;
			break;

		case 'P':						
			giroMonito--;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false && FrameIndex >1)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}


void menu( int id)
{
	
}



int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final Bob"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}