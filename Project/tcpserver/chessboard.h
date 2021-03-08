#ifndef CHESSBOARD_H
#define  CHESSBOARD_H
#include"ElementPool.h"
#include"qqueue.h"
class chessboard{
public:

	chessboard(QString,QString);
	~chessboard();
	QString player1;
	QString player2;
	ElementPool*_Elements;
	QQueue<int> AttackSequence;
	int Round;
	int readyPlayer;

	void initQueue();
	void initNewRound();
	int Next();
	int CheckVictory();
	void Remote_Archer(Element*element);
	void Melee_Archer(Element*element);
private:
	void initElementPool();

};
#endif