#include "board.h"
#include "academic.h"
#include "coop.h"
#include "dcTimsLine.h"
#include "goosenesting.h"
#include "goToTims.h"
#include "gym.h"
#include "needleshall.h"
#include "osap.h"
#include "residences.h"
#include "slc.h"
#include "tuition.h"
#include "textdisplay.h"
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include<fstream>
#include <sstream>
#include <stdexcept>
using namespace std;


vector<shared_ptr<Player>> Board::getPlayers(){
	return playerList;
}

vector<shared_ptr<Square>> Board::getSquares(){
	return squares;
}

int Board::getRollUpCards(){
	return rollUpCards;
}
void Board::setRollUpCards(int cards){
	rollUpCards=cards;
}

bool Board::isInTestMode(){
	return testMode;
}

void Board::setTesting(){
	testMode = true;
}

void Board::initSquares(){
	squares.push_back(make_shared<Osap>(shared_from_this(), "Osap", 0));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "AL", "Arts1", 1, 40, nullptr, 0, 50, AL));
	squares.push_back(make_shared<SLC>(shared_from_this(), "SLC1", 2));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "ML", "Arts1", 3, 60, nullptr, 0, 50, ML));
	squares.push_back(make_shared<Tuition>(shared_from_this(), "Tuition", 4));
	squares.push_back(make_shared<Residences>(shared_from_this(), "MKV", 5, nullptr));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "ECH", "Arts2", 6 , 100, nullptr, 0, 50, ECH));
	squares.push_back(make_shared<NeedlesHall>(shared_from_this(), "Needles Hall1", 7));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "PAS", "Arts2", 8, 100, nullptr, 0, 50, PAS));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "HH", "Arts2", 9, 120, nullptr, 0, 50, HH));
	squares.push_back(make_shared<DCTimsLine>(shared_from_this(), "DC Tims Line", 10));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "RCH", "Eng", 11, 140, nullptr, 0, 100, RCH));
	squares.push_back(make_shared<Gym>(shared_from_this(), "PAC", 12, nullptr));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "DWE", "Eng", 13, 140, nullptr, 0, 100, DWE));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "CPH", "Eng", 14, 160, nullptr, 0, 100, CPH));
	squares.push_back(make_shared<Residences>(shared_from_this(), "UWP", 15, nullptr));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "LHI", "Health", 16, 180, nullptr, 0, 100, LHI));
	squares.push_back(make_shared<SLC>(shared_from_this(), "SLC2", 17));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "BMH", "Health", 18, 180, nullptr, 0, 100, BMH));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "OPT", "Health", 19, 200, nullptr, 0, 100, OPT));
	squares.push_back(make_shared<GooseNesting>(shared_from_this(), "Goose Nesting", 20));		
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "EV1", "Env", 21, 220, nullptr, 0, 150, EV1));
	squares.push_back(make_shared<NeedlesHall>(shared_from_this(), "Needles Hall2", 22));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "EV2", "Env", 23, 220, nullptr, 0, 150, EV2));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "EV3", "Env", 24, 240, nullptr, 0, 150, EV3));
	squares.push_back(make_shared<Residences>(shared_from_this(), "V1", 25, nullptr));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "PHYS", "Sci1", 26, 260, nullptr, 0, 150, PHYS));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "B1", "Sci1", 27, 260, nullptr, 0, 150, B1));
	squares.push_back(make_shared<Gym>(shared_from_this(), "CIF", 28, nullptr));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "B2", "Sci1", 29, 280, nullptr, 0, 150, B2));
	squares.push_back(make_shared<GoToTims>(shared_from_this(), "Go To Tims", 30));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "EIT", "Sci2", 31, 300, nullptr, 0, 200, EIT));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "ESC", "Sci2", 32, 300, nullptr, 0, 200, ESC));
	squares.push_back(make_shared<SLC>(shared_from_this(), "SLC3", 33));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "C2", "Sci2", 34, 320, nullptr, 0, 200, C2));
	squares.push_back(make_shared<Residences>(shared_from_this(), "REV", 35, nullptr));
	squares.push_back(make_shared<NeedlesHall>(shared_from_this(), "Needles Hall3", 36));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "MC", "Math", 37, 350, nullptr, 0, 200, MC));
	squares.push_back(make_shared<Coop>(shared_from_this(), "Co-op Fee", 38));
	squares.push_back(make_shared<AcademicProperty>(shared_from_this(), "DC", "Math", 39, 400, nullptr, 0, 200, DC));
	for (int i=0; i<numOfSquares; i++){
		squares[i]->attach(td);
		squares[i]->notifyObservers();
	}
}

void Board::initialize(int numPlayers){
	vector<bool> piecesChosen;
	td = make_shared<TextDisplay>(shared_from_this());
	for(int i = 0; i < maxNumOfPlayers; i++){
		piecesChosen.push_back(false);
	}
	string name;
	string playerPiece;
	int i = 0;
	while(numPlayers != 0){
		while(true){
			cout << "Player " << i+1 << ": Enter your name: ";
                	cin>>name;
			if (name=="BANK"){
				cout << "Player cannot be named BANK" << endl;
				continue;
			}
			int currPlayers = playerList.size();
			bool taken=false;
			for (int i=0; i<currPlayers; i++){
				if (playerList[i]->getName()==name){
					cout << "Name already taken." << endl;
					taken = true;
					break;
				}
			}
			if(!taken)
				break;

		}
		cout << "Your options for pieces include (Type letter): " << endl;;


                for(int x = 0; x < maxNumOfPlayers; x++){
                        if(!piecesChosen[x])
                                cout << "\t" << pieces[x] << endl;
                }
		while(true){
                	cout << "Choose your piece: ";
 	                cin >> playerPiece;
        	        int counter = 0;
			int numOfPieces = pieces.size();
	                for(int y = 0; y < numOfPieces; y++){
        	                if(playerPiece[0] != pieces[y][0]){
                	                counter++;
                        	}
     	                   	else if(playerPiece[0] == pieces[y][0]){
        	                        piecesChosen[y] = true;
                	                counter = 0;
                	        }
               		}  
			if(counter == maxNumOfPlayers){  
  				cout << "This piece does not exist. Please select one of the available pieces." << endl;
                		continue;
			}
			break;
		}
		char piece_char = playerPiece[0];
                shared_ptr<Player> player = make_shared<Player>(piece_char, name, playerStartingMoney,0,0);
                playerList.push_back(player);
		numPlayers--;
		i++;        
	}
	
	initSquares();
	
	numOfPlayers = playerList.size();
	string waste;
	getline(cin,waste);
}



void Board::loadGame(string load){

	td = make_shared<TextDisplay>(shared_from_this());
	ifstream inp(load);
	string line = "";
	getline(inp, line);
	int numPlayers = stoi(line);
	if (numPlayers<2 || numPlayers>8){
		throw invalid_argument("Input file must have 2-8 players");
	}
	
	for (int i=0; i<numPlayers; i++){
		getline(inp, line);
		stringstream ss(line);
		string temp;
		vector<string> command;
		int currPlayers=i;
		while (ss >> temp){
			command.push_back(temp);
		}
		string player_name = command[0];
		if (player_name=="BANK"){
			throw invalid_argument("Player cannot be named Bank.");
		}
		for (int j=0; j<currPlayers; j++){
			if (playerList[j]->getName()==player_name){
				throw invalid_argument("A name is duplicated.");
			}
		}
		string player_piece = command[1];
		bool found=false;
		for (int j=0; j<maxNumOfPlayers; j++){
			if (pieces[j][0]==player_piece[0]){
				found = true;
			}	
		}
		if (!found){
			throw invalid_argument("This is not a valid piece.");
		}
		for (int j=0; j<currPlayers; j++){
			if (playerList[j]->getPiece()==player_piece[0]){
				throw invalid_argument("A piece is duplicated.");
			}
		}
		int cups = stoi(command[2]);
		if (cups+rollUpCards>4){
			throw invalid_argument("Too many Roll Up The Rims Cups");
		}
		int money = stoi(command[3]);
		if (money<0){
			throw invalid_argument("Cannot have negative money");
		}
		int jail = 0;
		int jailTurns = -1;
		int position = stoi(command[4]);
		if (position==goToJailSpace){
			throw invalid_argument("Cannot start on go to tims");
		}
		if (position==jailSpace){
			jail = stoi(command[5]);
			if (jail==1){
				jailTurns=stoi(command[6]);
				if (jailTurns<0 || jailTurns>2){
					throw invalid_argument("Jail turns must be between 0 and 2");
				}
			}
		}
                shared_ptr<Player> player = make_shared<Player>(player_piece[0], player_name, money,position,cups);
		if (jail==1){
			player->setJail(true);
			player->setJailTurns(jailTurns);
		}
                playerList.push_back(player);
		rollUpCards+=cups;
	}

	initSquares();
	int numOwnable = ownableIndex.size();
	for (int i=0; i<numOwnable; i++){
		shared_ptr<Square> square = squares[ownableIndex[i]];
		getline(inp, line);
		stringstream ss(line);
		string temp;
		vector<string> command;
		while (ss >> temp){
			command.push_back(temp);
		}

		if (command[0]==square->getName()){
			string owner = command[1];
			if (owner!="BANK"){
				bool found = false;
				for (int j=0; j<numPlayers; j++){
					if (owner==playerList[j]->getName()){
						found = true;
						square->setOwner(playerList[j]);
						if (!square->isImprovable() && square->isGym()){
							playerList[j]->addGym();
						}
						if (!square->isImprovable() && !square->isGym()){
							playerList[j]->addRes();
						}
						playerList[j]->addSquare(square);
						break;
					}
				}
				if(!found){
					throw invalid_argument("Not a valid owner");
				}
			}

			int improvements = stoi(command[2]);
			if (improvements<-1 || improvements>5){
				throw invalid_argument("Improvements must between -1(Mortgaged) and 5");
			}
			if (improvements>0 && !(square->isImprovable())){
				throw invalid_argument("Improvements for not improvable properties must be 0, or -1(mortgaged)");
			}
			square->setImprovementLevel(improvements);	
		}
	}

	for (int i=0; i<numOfSquares; i++){
		if (squares[i]->getImprovementLevel()>0){
			string owner = squares[i]->getOwner()->getName();
			string block = squares[i]->getMonopolyBlock();
			for(int i = 0; i < numOfSquares; i++){
				shared_ptr<Square> square = squares[i];
				if(square->getMonopolyBlock() == block && !(square->getOwner()->getName()==owner)){
						throw invalid_argument("Improvements cannot be made if whole block is not owned by the same person.");
				}
			}	
		}
	}
	
	for (int i=0; i<numOfSquares; i++){
		squares[i]->notifyObservers();
	}
	cout << "Game Successfully Loaded" << endl;
}

void Board::saveGame(string filename, int index){
	ofstream file;
	file.open(filename);
	int numPlayers = playerList.size();
	file << numPlayers << endl;
	for (int i=0; i<numPlayers; i++){
		shared_ptr<Player> player = playerList[(index+i)%numPlayers];
		string playerstring = "";
		playerstring+=player->getName()+" ";
		playerstring+=player->getPiece();
		playerstring+=" ";
		playerstring+=to_string(player->getTimCups()) + " ";
		playerstring+=to_string(player->getMoney()) + " ";
		playerstring+=to_string(player->getPosition());
		if (player->getPosition()==jailSpace){
			if(player->isInJail()){
				playerstring+=" 1 "+to_string(player->getJailTurns());
			}
			else{
				playerstring+=" 0";
			}
		}
		file << playerstring << endl;
	}
	int numOwnable = ownableIndex.size();
	for (int i=0; i<numOwnable; i++){
		shared_ptr<Square> square = squares[ownableIndex[i]];
		string square_string = square->getName();
		if (square->getOwner()){
			square_string += " " + square->getOwner()->getName();
		}
		else{
			square_string += " BANK";
		}
		if (square->isMortgaged()){
			square_string += " -1";
		}
		else{
			square_string += " " + to_string(square->getImprovementLevel());
		}
		file << square_string << endl;
	}
	file.close();	
	cout << "Saved to " << filename << "." << endl;
}

void Board::displayOption(shared_ptr<Player> player){
	cout << "It is now " << player->getName() << "'s turn. These are your options: " << endl;
	if (player->isInJail()){
		cout << "\t next (will go through jail steps, and  end your turn)" << endl;;
	}
	else{
		if(testMode){
			cout << "\t roll <die1> <die2> (will end your turn)" << endl;
		}
		cout << "\t roll (will end your turn)" << endl;
	}
	cout << "\t \t your turn may end after you choose next or roll, please do everything before this point." << endl;
	cout << "\t trade <name> <property> <money>" << endl;
	cout << "\t trade <name> <property> <property>" << endl;
	cout << "\t trade <name> <money> <property>" << endl;
	cout << "\t improve <property> buy/sell" << endl;
	cout << "\t mortgage <property>" << endl;
	cout << "\t unmortgage <property>" << endl;
	cout << "\t assets" << endl;
	cout << "\t all" << endl;
	cout << "\t save <filename>" << endl;
	cout << "\t quit" << endl;
}
void Board::trade(vector<string> command, int currPlayer){
      if (command.size() == 4) {
	      int index=-1;
	      int size = playerList.size();
	      for (int i=0; i<size; i++){
			if (playerList[i]->getName()==command[1]){
				index = i;
				break;
			}
	      }
	      if (index==-1){
                        cout << "Player: " << command[1]  <<" doesn't exist" << endl;
			return;
	      }
	      shared_ptr<Player> current = playerList[currPlayer];
	      shared_ptr<Player> other = playerList[index];

	      int value=-1;
	      try{
	      	value = stoi(command[3]);
	      }
	      catch(exception &err){
	      }
	      int value2=-1;
	      try{
	      	value2 = stoi(command[2]);
	      }
	      catch(exception &err){
	      }

	      if (value>-1 && value>-1){
			cout << "You can't trade money for money" << endl;
			return;
	      }
	      if (value>-1){
		     vector<shared_ptr<Square>> mySquares = current->getSquares();
		     int numPropOwned = mySquares.size();
	             int square_index=-1;
	      	     string accept="";
		     for (int i=0; i<numPropOwned; i++){
			if (mySquares[i]->getName()==command[2]){
				square_index=i;
				break;
			}
		     }
		     if (square_index==-1){
                                cout << "You don't own "<< command[2] <<"." << endl;
				return;
		     }

		     if (mySquares[square_index]->isImprovable()){
		     	string mono_block = mySquares[square_index]->getMonopolyBlock();
		     	for (int i=0; i<numPropOwned; i++){
				if (mySquares[i]->getMonopolyBlock()==mono_block && mySquares[i]->getImprovementLevel()>0){
                                        cout << mySquares[i]->getName() << " has improvements." << endl;
					cout << "Cannot trade when the property, or properties in the same block, have improvements" << endl;
					return;
				}
		     	}
		     }

		     if (other->getMoney()<value){
                                cout << command[1] << "  doesn't have enough money" << endl;
				cout<<"The other player doesn't have enough money"<<endl;
				return;
		     }
		     cout << "Does " << command[1] << " accept the trade (type accept to accept)" << endl;
		     getline(cin,accept);
		     if (accept!="accept"){
			cout << command[1] << " has not accepted." << endl;
			return;
		     }
		    current->transferProperty(other, mySquares[square_index], playerList);
		    other->subtractMoney(value, playerList);
		    current->addMoney(value);
	      		
		    return;
	      }
	     
	      	      
      	      if (value2>-1){
                     
		     vector<shared_ptr<Square>> otherSquares = other->getSquares();
		     int numPropOwned = otherSquares.size();
	             int square_index=-1;
	      	     string accept="";
		     
		     for (int i=0; i<numPropOwned; i++){
                        if (otherSquares[i]->getName()==command[3]){
                                square_index=i;
                                break;
                        }
                     }
                     if (square_index==-1){
                                cout<< command[1] << " doesn't own " << command[3] << "." <<endl;
                                return;
                     }
                     
		    
		     if (otherSquares[square_index]->isImprovable()){
		     	string mono_block = otherSquares[square_index]->getMonopolyBlock();
		     	for (int i=0; i<numPropOwned; i++){
				if (otherSquares[i]->getMonopolyBlock()==mono_block && otherSquares[i]->getImprovementLevel()>0){
                                        cout << otherSquares[i]->getName() << " has improvements." << endl;
					cout << "Cannot trade when the property, or properties in the same block, have improvements" << endl;
					return;
				}
		     	}
		     }

		     if (current->getMoney()<value2){
                                cout<<"You don't have enough money."<<endl;
                                return;
                     }
                     cout << "Does " << command[1] << " accept the trade (type accept to accept)" << endl;
                     getline(cin,accept);
                     if (accept!="accept"){
                        cout << command[1] << " has not accepted." << endl;
                        return;
                     }
                    other->transferProperty(current, otherSquares[square_index], playerList);
                    current->subtractMoney(value, playerList);
                    other->addMoney(value);

                    return;
              }


	
	      vector<shared_ptr<Square>> mySquares = current->getSquares();
              int numPropOwned = mySquares.size();
              int square_index=-1;
              string accept="";
              for (int i=0; i<numPropOwned; i++){
              	     if (mySquares[i]->getName()==command[2]){
                          square_index=i;
                          break;
                     }
              }
              if (square_index==-1){
                        cout << "You don't own "<< command[2] <<"." << endl;
                        return;
              }


	      if (mySquares[square_index]->isImprovable()){
		     	string mono_block = mySquares[square_index]->getMonopolyBlock();
		     	for (int i=0; i<numPropOwned; i++){
				if (mySquares[i]->getMonopolyBlock()==mono_block && mySquares[i]->getImprovementLevel()>0){
                                        cout << mySquares[i]->getName() << " has improvements." << endl;
					cout << "Cannot trade when the property, or properties in the same block, have improvements" << endl;
					return;
				}
		     	}
	      }

	      

	      vector<shared_ptr<Square>> otherSquares = other->getSquares();
              int numPropOwnedOther = otherSquares.size();
              int square_index_other=-1;
              for (int i=0; i<numPropOwnedOther; i++){
                     if (otherSquares[i]->getName()==command[3]){
                          square_index_other=i;
                          break;
                     }
              }
              if (square_index_other==-1){
                        cout<<command[1] <<" doesn't own " << command[3] << "." <<endl;
                        return;
              }

	      if (otherSquares[square_index_other]->isImprovable()){
		     	string mono_block = otherSquares[square_index_other]->getMonopolyBlock();
		     	for (int i=0; i<numPropOwnedOther; i++){
				if (otherSquares[i]->getMonopolyBlock()==mono_block && otherSquares[i]->getImprovementLevel()>0){
                                        cout << otherSquares[i]->getName() << " has improvements." << endl;
					cout << "Cannot trade when the property, or properties in the same block, have improvements" << endl;
					return;
				}
		     	}
	      }
              cout << "Does " << command[1] << " accept the trade (type accept to accept)" << endl;
              getline(cin,accept);
              if (accept!="accept"){
                   cout << command[1] << " has not accepted." << endl;
                     return;
                   }
	      current->transferProperty(other, mySquares[square_index], playerList);
              other->transferProperty(current,otherSquares[square_index_other], playerList);
	      return;
      }
}
	
	
vector<int> Board::rollDice(int die1, int die2){
	if(die1==-1){
		srand (time(NULL));
        	die1 = rand() % 6 + 1;
		die2 = rand() % 6 + 1;
	}
	vector<int> rolls = {die1, die2};	
	return rolls;
}
	
void Board::play(){
	int currPlayer = 0;
	string line = "";
	bool ended = false;
	td->print();
	displayOption(playerList[currPlayer]);
	cout << "Enter Input: " << endl;
	int doubles=0;
	
	while(!ended){
		shared_ptr<Player> player = playerList[currPlayer];
		int numPlayer = playerList.size();
		if (numPlayer<2){
			cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
			cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
			cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
			ended=true;
			break;
		}
		getline(cin, line);
		stringstream ss(line);
		string temp;
		vector<string> command;
		while (ss >> temp){
			command.push_back(temp);
		}
		if(command.size()<1){
			continue;
		}
		if (command[0]=="quit"){
			ended=true;
			break;
		}
		else if(command[0] == "roll"){
			if (player->isInJail()){
				cout << "You are not eligible to roll, and this command is invalid. Use next, to end you turn. " << endl;
				continue;
			}
			vector<int> roll;
			int totalRoll;
			if(!testMode)
				roll=rollDice(-1, -1);
			else{
				if(command.size()==3 && command[1] != "" && command[2] != ""){
					try{	
						roll = rollDice(stoi(command[1]), stoi(command[2]));
					}
					catch(const invalid_argument &ia){
						roll = rollDice(-1, -1);
					}
				}
				else{
					roll = rollDice(-1, -1);
				}
			}
			totalRoll = roll[0] + roll[1];
			int oldpos = player->getPosition();
			player->move(totalRoll);
			
			while(player->getPosition() >= numOfSquares){
				player->move(-numOfSquares);
				squares[0]->action(player);
			}

			squares[oldpos]->notifyObservers();
			squares[player->getPosition()]->notifyObservers();
			
			td->print();
			cout << "Your rolled " << roll[0] << " and " << roll[1] << endl;
			cout << "You landed on: " << squares[player->getPosition()]->getName() << endl;
			if ((player->getPosition()!=osapSpace)&&(player->getPosition()!=jailSpace)){
				squares[player->getPosition()]->action(player);
			}
			if (player->getPosition()<0){
				player->move(numOfSquares);
			}
			if (player->isBankrupt()){
				cout << "You have been bankrupted, your piece will now be removed." << endl;
				numOfPlayers--;
				int oldpos=player->getPosition();
				player->setPosition(-1);
				squares[oldpos]->notifyObservers();
				playerList.erase(playerList.begin()+currPlayer);
				if (numOfPlayers==1){
					cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
					cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
					cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
					ended=true;
				}
			}

			if(roll[0] != roll[1] || player->isBankrupt()){
				doubles=0;			
				currPlayer = (currPlayer+1)%numOfPlayers;
				cout << "It is now the next player's turn" << endl;
				displayOption(playerList[currPlayer]);
			}
			else{
				doubles++;
				if(doubles==3){
					cout << "You rolled three doubles, you are sent to jail." << endl;
					playerList[currPlayer]->setPosition(jailSpace);
					playerList[currPlayer]->setJail(true);
					playerList[currPlayer]->setJailTurns(0);
					currPlayer = (currPlayer+1)%numOfPlayers;
					cout << "It is now the next player's turn" << endl;
					displayOption(playerList[currPlayer]);
				}
				else{
					cout << "You rolled doubles. Take your turn again." << endl;
			
				}
			}
			
		}		
		else if(command[0] == "next"){
			if (!(player->isInJail())){
				cout << "You are eligible to roll, and this command is invalid. " << endl;
				continue;
			}

			cout << "You are in jail" << endl;
			squares[player->getPosition()]->action(playerList[currPlayer]);
			
			if (player->isBankrupt()){
				cout << "You have been bankrupted, your piece will now be removed." << endl;
				numOfPlayers--;
				playerList.erase(playerList.begin()+currPlayer);
				if (numOfPlayers==1){
					cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
					cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
					cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
					ended=true;
				}
			}			
			if(playerList[currPlayer]->getPosition()!=jailSpace){
				squares[player->getPosition()]->action(player);
				squares[jailSpace]->notifyObservers();
				squares[player->getPosition()]->notifyObservers();
				if (player->isBankrupt()){
					cout << "You have been bankrupted, your piece will now be removed." << endl;
					numOfPlayers--;
					playerList.erase(playerList.begin()+currPlayer);
					if (numOfPlayers==1){
						cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
						cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
						cout << "The game is now over. The winner is " << playerList[0]->getName() << "." << endl;
						ended=true;
					}
				}
				
				if (player->getJailLastRoll()[0]==player->getJailLastRoll()[1]){
					doubles=1;
					continue;
				}			
			}

			currPlayer++;
			if(currPlayer>=numOfPlayers){
				doubles=0;
				currPlayer=0;
			}
			cout << "It is now the next player's turn" << endl;
			displayOption(playerList[currPlayer]);
		}	
		else if(command[0] == "improve"){
			if (command.size()<3){
				continue;
			}
			string property = command[1];
			for(int i = 0; i < numOfSquares; i++){
				shared_ptr<Square> academicProperty = squares[i];
				if(academicProperty->getName() == property && academicProperty->isImprovable()){
					if(command[2] == "sell"){
						academicProperty->improveSell(player);
					}
					else if(command[2] == "buy"){
						academicProperty->improveBuy(player);
					}
					else{
						cout << "Invalid command. Please enter one of the commands given." << endl;
					}	
					break;
				}
			}
		}
		else if(command[0] == "mortgage"){
			if (command.size()<2){
				continue;
			}
			string property = command[1];
                	for(int i = 0; i < numOfSquares; i++){     
					shared_ptr<Square> square = squares[i];  
					if(square->getName() == property){
						if(!(square->isMortgaged() || square->getImprovementLevel()==-1)
							&&(playerList[currPlayer]->getName() == square->getOwner()->getName())){	  
								square->mortgage(player);
								break;
						}
                                                cout << "Invalid command. Please enter one of the commands given." << endl;                                                                                               		     break;
				       }
			}	
		}
		else if(command[0] == "unmortgage"){
			if (command.size()<2){
				continue;
			}
                        string property = command[1];
			
                        for(int i = 0; i < numOfSquares; i++){
                                shared_ptr<Square> square = squares[i];
				if(square->getName() == property){
				       if((square->isMortgaged()||square->getImprovementLevel()==-1) && 
						player->getName() == square->getOwner()->getName()){
                                		square->unmortgage(player); 
						break;
				       }	
                                       cout << "Invalid command. Please enter one of the commands given." << endl;
				       break;
				}            
                        }
                }
		else if(command[0] == "assets"){
			player->printPlayerAssets();
		}
		else if(command[0] == "all"){ 
			for(int i = 0; i < numOfPlayers; i++){
	                        playerList[i]->printPlayerAssets();
				cout << endl;
			}
                        
                }
		else if (command[0] == "trade"){
			if (command.size()<4){
				continue;
			}
			trade(command, currPlayer);
		}
		else if (command[0]=="save"){
			if (command.size()<2){
				continue;
			}
			saveGame(command[1], currPlayer);
		}
		else{
			cout << "Enter a valid command" << endl;
		}
		cout << "Enter Input: " << endl;
	}
}


