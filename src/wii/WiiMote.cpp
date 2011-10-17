/*
 * WiiMote.cpp
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#define TAMANHO 12 //tamanho max da fila
#define VAR_ACX_POS 12		//valor antigo 9 e -9
#define VAR_ACX_NEG -12
#define VAR_ACY_POS 9           //valor anterior -3
#define VAR_ACY_NEG -9  //anterior = -10
#define VAR_IRX_POS 320   //anterior = 160
#define VAR_IRX_NEG -320
#define MENOR_DIST 2
#define MAIOR_DIST 8
#define TIMEOUT 3

#include "../../include/AccelerationEvent.h"
using namespace ::br::ufscar::lince::mmi;

#include "../../include/wii/WiiMote.h"
#include "../../include/wii/StateCircularBuffer.h"
#include "../../include/wii/WiiButtonReport.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

const unsigned char WiiMote::REPORT_BUTTONS = 1;
const unsigned char WiiMote::REPORT_ACCELERATION = 2;
const unsigned char WiiMote::REPORT_MOVES = 4;
const unsigned char WiiMote::REPORT_ALL = 7;

WiiMote::WiiMote(WiiEventHandler* handler, unsigned char reportEvents) : Thread() {
	this->handler = handler;
	this->reportEvents = reportEvents;

	wiiDriver = new WiiDriver();
	wiiDriver->setAccelerometer(true);
	wiiDriver->setButtons(true);

	buffer = new StateCircularBuffer(10);

	buttonReport = NULL;
}

WiiMote::~WiiMote() {
	// TODO Auto-generated destructor stub
}

void WiiMote::connect() {
	start();
}

void  WiiMote::disconnect() {
	//TODO: Parar thread e desconectar as coisas
}

void WiiMote::sendToDevice(vector<string>* args) {
	//TODO: Implementar acendejobr a luz dos leds
}

string WiiMote::getDeviceId() {
	return deviceName;
}

 void WiiMote::release() {

}

void WiiMote::run() {
	wiiDriver->connect();
		deviceName = "wiimote1";

	if (isReportingButtons()) {
		buttonReport = new WiiButtonReport(deviceName, handler, wiiDriver);
	}

	//Sinalizão que um movimento foi encontrado
	bool movimentoVerticalCima = false;
	bool movimentoVerticalBaixo = false;
	bool movimentoHorizontalDir = false;
	bool movimentoHorizontalEsq = false;
	bool movimentoAccXEsq = false;
	bool movimentoAccXDir = false;

	//Marcão as variações de cada unidade
	int variacaoAccX = 0;
	int variacaoAccY = 0;
	int variacaoIr1 = 0;
	int variacaoIr2 = 0;

	//Utilizado para se obter os valores dos centros de massa.
	int centroMassaAccX = 0;
	int centroMassaAccY = 0;
	int centroMassaIr1 = 0;
	int centroMassaIr2 = 0;

	//Utilizados para se obter os valores
	int valorIr1 = 0;
	int valorIr2 = 0;
	int valorAccX = 0;
	int valorAccY = 0;

	//Não faço a menor ideia
	int distanciaEntrePontos = 0;

	bool achouCima, achouBaixo, achouDireita, achouEsquerda, achouAccXDir, achouAccXEsq;
	achouCima = achouBaixo = achouDireita = achouEsquerda = achouAccXDir = achouAccXEsq = false;

	bool achouRecomeca = false;

	WiiState* state;
	WiiEvent *event;

	if (isReportingButtons()) {
		buttonReport->start();
	}
	state = wiiDriver->getCurrentState();
	buffer->insert(state);

	//variaveis para contagem de tempo
	time_t tempoi, tempof;
	double tempoTotal;
	time(&tempoi);

	while (true) {
		while (!achouRecomeca) {
			//zera movimentos a cada iteração
			movimentoVerticalCima = false;
			movimentoVerticalBaixo = false;
			movimentoHorizontalDir = false;
			movimentoHorizontalEsq = false;
			movimentoAccXDir = false;
			movimentoAccXEsq = false;

			//verifica variacao nos eixos x e y dos acelerometros
			while (variacaoAccX >= VAR_ACX_NEG && variacaoAccX <= VAR_ACX_POS &&
					variacaoAccY >= VAR_ACY_NEG && variacaoAccY <= VAR_ACY_POS &&
					variacaoIr1 >= VAR_IRX_NEG && variacaoIr1 <= VAR_IRX_POS &&
					variacaoIr2 >= VAR_IRX_NEG && variacaoIr2 <= VAR_IRX_POS &&
					!achouRecomeca) {

				usleep(100); //leitura em microsegundos
				state = wiiDriver->getCurrentState();

				if (isReportingAcceleration()) {
					AccelerationEvent* accEvent = new AccelerationEvent(deviceName,
							state->getAccelationX(),
							state->getAccelationY(),
							state->getAccelationZ());

					handler->sendEvent(accEvent);
				}

				if(state->isButtonPressed(BUTTON_A)){
					achouRecomeca = true;
					cout << "Botao A pressionado" << endl;
				}

				//cout<< "accX: " << state->getAccelationX() << endl;
				//cout<< "accY: " << state->getAccelationY() << endl;
				//cout<< "accZ: " << state->getAccelationZ() << endl;

				valorAccX = state->getAccelationX();
				valorAccY = state->getAccelationY();
				buffer->insert(state);

				centroMassaAccX = this->evalueMassCenterAccX();
				centroMassaAccY =  this->evalueMassCenterAccY();


				variacaoAccX = centroMassaAccX - state->getAccelationX();
				variacaoAccY = centroMassaAccY - state->getAccelationY();

				time(&tempof);  //tempo final
				tempoTotal = tempof - tempoi;
				//cout << "Tempo total: " << tempoTotal << endl;

				//reseta movimentos caso time-out
				if (tempoTotal > TIMEOUT) {
					tempoi = 0;
					time(&tempoi);
					tempof = 0;
					time(&tempof);
					tempoTotal = 0;
					//cout << "Resetando variaveis!!\n";
					achouBaixo = achouCima = achouDireita = achouEsquerda = false;
					achouAccXEsq = achouAccXDir = false;
				}
			}

			//zera contagem de tempo para resetar
			tempoi = 0;
			time(&tempoi);
			tempof = 0;
			time(&tempof);
			tempoTotal = 0;

			if (isReportingMoves()) {
				//cout<< "variacaoAccX: " << variacaoAccX << endl;
				//cout<< "variacaoAccY: " << variacaoAccY << endl;

				if ((variacaoAccX < VAR_ACX_NEG || variacaoAccX > VAR_ACX_POS)
						&& achouRecomeca == false) {
					if (variacaoAccX < VAR_ACX_NEG) {

						event = new WiiEvent(deviceName, RIGHT);
						handler->sendEvent(event);
						achouAccXEsq = true;
						movimentoAccXEsq = true;
					} else {
						if (variacaoAccX > VAR_ACX_POS) {
							event = new WiiEvent(deviceName, LEFT);
							handler->sendEvent(event);
							achouAccXDir = true;
							movimentoAccXDir = true;
						}
					}
				} else {
					//prototipo movimento vertical
					if ((variacaoAccY < VAR_ACY_NEG || variacaoAccY > VAR_ACY_POS)
							&& achouRecomeca == false) {
						distanciaEntrePontos = (int) sqrt((
								pow(valorAccX - centroMassaAccX,2)) +
								(pow(valorAccY - centroMassaAccY,2)));

						if (distanciaEntrePontos >= MENOR_DIST
								/*&& distanciaEntrePontos <= MAIOR_DIST*/) {

							if (variacaoAccY > VAR_ACY_POS) {
								movimentoVerticalCima = true;
								achouCima = true;
								event = new WiiEvent(deviceName, UP);
								handler->sendEvent(event);
							} else {
								if (variacaoAccY < VAR_ACY_NEG) {
									movimentoVerticalBaixo = true;
									achouBaixo = true;
									event = new WiiEvent(deviceName, DOWN);
									handler->sendEvent(event);
								}
							}
						}
					}
				}
			}

			//movimento cima baixo simples
			if (movimentoVerticalCima || achouCima) {
				if (movimentoVerticalBaixo && !achouEsquerda && !achouDireita) {
					//cout << "                                                Aumenta volume\n";
					achouCima = false;
					achouBaixo = false;
					achouDireita = false;
					achouEsquerda = false;
					//event = new WiiEvent("WII_UP_DOWN");
					//handler->sendEvent(event);
				}
			}

			//movimento baixo cima simples
			if (movimentoVerticalBaixo || achouBaixo) {
				if (movimentoVerticalCima && !achouEsquerda && !achouDireita) {
					//cout << "                                                Diminui volume\n";
					achouBaixo = false;
					achouCima = false;
					achouDireita = false;
					achouEsquerda = false;
					//event = new WiiEvent("WII_DOWN_UP");
					//handler->sendEvent(event);
				}
			}

			//movimento esquerda accX
			if (movimentoAccXEsq || achouAccXEsq) {
				if (movimentoAccXDir && !achouEsquerda && !achouDireita) {
					//cout << "                                                Avanca canal\n";
					achouAccXDir = achouAccXEsq = false;
					achouBaixo = false;
					achouCima = false;
					achouDireita = false;
					achouEsquerda = false;
					//event = new WiiEvent("WII_LEFT_RIGHT");
					//handler->sendEvent(event);
				}
			}

			//movimento direita accX
			if (movimentoAccXDir || achouAccXDir) {
				if (movimentoAccXEsq && !achouEsquerda && !achouDireita) {
					//cout << "                                                Retrocede canal\n";
					achouAccXDir = achouAccXEsq = false;
					achouBaixo = false;
					achouCima = false;
					achouDireita = false;
					achouEsquerda = false;
					//event = new WiiEvent("WII_RIGHT_LEFT");
					//handler->sendEvent(event);
				}
			}

			//movimentos invalidos
			if (movimentoVerticalCima || achouCima
					|| movimentoVerticalBaixo || achouBaixo) {

				if (movimentoAccXEsq || movimentoAccXDir) {
					//cout << "Movimento invalido!" << endl;
					achouAccXDir = achouAccXEsq = false;
					achouBaixo = false;
					achouCima = false;
					achouDireita = false;
					achouEsquerda = false;
				}
			}

			//movimentos invalidos
			if (movimentoAccXDir || achouAccXDir ||
					movimentoAccXEsq || achouAccXEsq) {
				if (movimentoVerticalCima || movimentoVerticalBaixo) {
					//cout << "Movimento invalido!" << endl;
					achouAccXDir = achouAccXEsq = false;
					achouBaixo = false;
					achouCima = false;
					achouDireita = false;
					achouEsquerda = false;
				}
			}


			//estabiliza variacao acc
			while ((variacaoAccY < VAR_ACY_NEG || variacaoAccY > VAR_ACY_POS) ||
					(variacaoAccX < VAR_ACX_NEG || variacaoAccX > VAR_ACX_POS)) {
				//le estado do controle novamente para calcular variação do ponto lido e o centro de massa
				usleep(40); //leitura em microsegundos
				state = wiiDriver->getCurrentState();

				if(state->isButtonPressed(BUTTON_A)){
					achouRecomeca = true;
					//cout << "Botao A pressionado" << endl;
				}

				buffer->insert(state);

				centroMassaAccX = this->evalueMassCenterAccX();
				centroMassaAccY = this->evalueMassCenterAccY();

				variacaoAccX = centroMassaAccX - state->getAccelationX();
				variacaoAccY = centroMassaAccY - state->getAccelationY();
			}

			variacaoAccX = 0;
			variacaoAccY = 0;
		}

		achouAccXDir = achouAccXEsq = false;
		achouBaixo = false;
		achouCima = false;
		achouDireita = false;
		achouEsquerda = false;
		achouRecomeca = false;

		//leitura do controle
		state = wiiDriver->getCurrentState();
	}
}

int WiiMote::evalueMassCenterAccX() {
	 WiiState* state = buffer->getBegin();
	 double value = 0;
	 while (state != NULL) {
		 value += state->getAccelationX();
		 state = buffer->getNext();
	 }
	 return (int) (value/buffer->getCurrentSize());
}

int WiiMote::evalueMassCenterAccY() {
	 WiiState* state = buffer->getBegin();
	 double value = 0;
	 while (state != NULL) {
		 value += state->getAccelationY();
		 state = buffer->getNext();
	 }
	 return (int) (value/buffer->getCurrentSize());
}

int WiiMote::evalueMassCenterAccZ() {
	 WiiState* state = buffer->getBegin();
	 double value = 0;
	 while (state != NULL) {
		 value += state->getAccelationZ();
		 state = buffer->getNext();
	 }
	 return (int) (value/buffer->getCurrentSize());
}

bool WiiMote::isReportingButtons() {
	return (bool) (reportEvents & REPORT_BUTTONS);
}

bool WiiMote::isReportingAcceleration() {
	return (bool) (reportEvents & REPORT_ACCELERATION);
}

bool WiiMote::isReportingMoves() {
	return (bool) (reportEvents & REPORT_MOVES);
}


}
}
}
}
}
