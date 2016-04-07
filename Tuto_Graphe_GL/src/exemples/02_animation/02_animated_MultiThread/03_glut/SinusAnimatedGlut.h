#pragma once

#include "SinusGraphe.h"
#include "GLUTMultithreadWindow.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Rappel:
 *
 * 	Glut est mono thread
 * 	Le glut-thread est m�me le main-thread
 *
 * Animation Standard (mecanismes par defaut)
 * 	Dans les examples precedents, l'animation etait orchestrer par idleFunc.
 * 	Glut apelle p�riodiquement dans son glut-thread le callback idleFunc.
 * 	idleFunc est redefini dans GLUTGraphWindow, qui appelle animationStep de Curve ou tout autre figure
 *
 * Animation:
 * 	L'objectif est ici d'utiliser un thread separer (donc different de glut-thread)
 * 	L'avantage est qu'ici il y a un thread fenetre,au lieu de 1 pour toute les fen�tres.
 * 	=> Plus performant si calcul complexe
 *
 * Note:
 * 	Les deux m�canimes d'animation peuvent cohabiter et �tre utiliser en meme temps.
 *
 * Technique:
 *
 * 	Cette animation dans cette api s'appelle animation "post-rendu", car une methode
 *
 * 		postRender
 *
 * 	est appeller apr�s le rendu initial d'une fen�tre vide.
 * 	Dans cette m�thode on code une boucle infinie qui joue l'animation.
 * 	Cette m�thode est appeler par un autre que le glut-thread.
 * 	Ce thread est transparent pour l'utilisateur.
 *
 * Conclusion:
 *
 * 	Pour le user, il faut
 *
 * 		(C1) setAnimationEnable(true) sur son objet graphe
 * 		(C2) Utiliser GLUTMultithreadWindow au lieu de GLUTGraphWindow
 *
 */
class SinusAnimatedGlut
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	SinusAnimatedGlut(int w, int h, int px, int py);

	virtual ~SinusAnimatedGlut();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:


	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Tools
	SinusGraphe* ptrGraphe;
	GLUTMultithreadWindow* ptrGLUTMultithreadWindow;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
