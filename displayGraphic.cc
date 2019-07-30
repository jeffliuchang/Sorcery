#include <iostream>
#include <cstring>
#include <string>
#include "displayGraphic.h"
#include "cardtype.h"


// Minion is Orange, Spell is Green, Enchantment is Yellow, Ritual is Brown, Player is Black with white string.
// Middle "Sorcery" for board is Black, with white "sorcery".
void describe_minion(Minion minion) {
	int line, length;
	int size = minion.getEnchants().size();
	int row = (size % 5 == 0) ? (size / 5) + 1 : (size / 5) + 2;
	int col = (size / 5 == 0)? size % 5 : 5;
	if (size == 0) col = 1;
	Xwindow xw(col*180, row*120);

	// draw the Minion itself
	xw.fillRectangle(0, 0, 180, 120, Xwindow::Orange);
	xw.fillRectangle(180, 0, 180*col, 120, Xwindow::White);
	std::string desc = minion.getActivated().getDescription();
	if (desc == "NA") {
		desc = minion.getTriggered().getDescription();
		if (desc == "NA") desc = "";
		line = 0;
                length = desc.length();
                for (int i = 0; i < length; ++i) {
			int len = ((length - i) < 25) ? (length-i) : 25;
                        xw.drawString(10, 60 + (14*line), desc.substr(i, len));
                        i += (len-1);
                        ++line;
		}
	} else {
		int line = 0;
               	int length = desc.length();
                for (int j = 0; j < length; ++j) {
			int len = ((length - j) < 22) ? (length-j) : 22;
                        xw.drawString(35, 65 + (15*line), desc.substr(j, len));
                        j += (len-1);
                        ++line;
		}
	}

	xw.drawString(130, 40, "Minion");
        xw.drawString(10, 20, minion.getName()); // name
        xw.drawString(160, 20, std::to_string(minion.getCost())); // cost
        xw.drawString(10, 110, std::to_string(minion.atk)); // attack
        xw.drawString(160, 110, std::to_string(minion.def)); // defence
        if (minion.getActivated().getDescription() != "NA") { // actCost
		xw.drawString(10, 65, std::to_string(minion.getActivated().getCost()));
		xw.drawLine(0, 75, 25, 75); // horizontal line
		xw.drawLine(25, 45, 25, 75); // vertical line
	}
	xw.drawLine(0, 25, 180, 25); // first horizontal line
	xw.drawLine(0, 45, 180, 45); // second horizontal line
	xw.drawLine(140, 0, 140, 25); // upper right vertical line
                
	xw.drawLine(0, 90, 30, 90); // left box horizontal line
	xw.drawLine(30, 90, 30, 120); // left box vertical line
	xw.drawLine(145, 90, 180, 90); // right box horizontal line
	xw.drawLine(145, 90, 145, 120); // right box vertical line


	// draw the enchantments
	std::string name;
	for (int a = 1; a < row; ++a) {
		int rest = ((size - ((a-1)*5)) < 5) ? (size - ((a-1)*5)) : 5;
		for (int j = 0; j < rest; ++j) {
			name = minion.getEnchants().at(5*(a-1)+j).getName();

			xw.fillRectangle(180*j, 120*a, 180, 120, Xwindow::Yellow);
			xw.drawString(130+(180*j), 40+(120*a), "Enchantment");
			xw.drawString(10+(180*j), 20+(120*a), name); // name
			xw.drawString(160+(180*j), 20+(120*a), std::to_string(minion.getEnchants().at(5*(a-1)+j).getCost())); // cost

			xw.drawLine(180*j, 25+(120*a), 180+(180*j), 25+(120*a)); // first horizontal line
			xw.drawLine(180*j, 45+(120*a), 180+(180*j), 45+(120*a)); // second horizontal line
			xw.drawLine(140+(180*j), 120*a, 140+(180*j), 25+(120*a)); // upper right vertical line
			
			desc = minion.getEnchants().at(5*(a-1)+j).getDes();
			line = 0;
                	length = desc.length();
                	for (int i = 0; i < length; ++i) {
				int len = ((length - i) < 25) ? (length-i) : 25;
				xw.drawString(10+(180*j), 65 + (15*line) + (120*a), desc.substr(i, len));
				i += (len-1);
                        	++line;
			}

			if (name == "Giant Strength") {
				xw.drawString(10+(180*j), 110+(120*a), "+2");
                		xw.drawString(160+(180*j), 110+(120*a), "+2");
			} else if (name == "Enrage") {
				xw.drawString(10+(180*j), 110+(120*a), "*2");
                                xw.drawString(160+(180*j), 110+(120*a), "*2");
			}
			if ((name == "Giant Strength") || (name == "Enrage")) {
				xw.drawLine(180*j, 90+(120*a), 30+(180*j), 90+(120*a)); // left box horizontal line
                		xw.drawLine(30+(180*j), 90+(120*a), 30+(180*j), 120+(120*a)); // left box vertical line
                		xw.drawLine(145+(180*j), 90+(120*a), 180+(180*j), 90+(120*a)); // right box horizontal line
                		xw.drawLine(145+(180*j), 90+(120*a), 145+(180*j), 120+(120*a)); // right box vertical line
			}
		}
	}
	// fill in possible blanks
	if (size%5 != 0) xw.fillRectangle(size%5*180, 120*(row-1), 900, 120*row, Xwindow::White);
	// draw boarders
	for (int i = 1; i < row; ++i) xw.drawLine(0, 120*i, 180*col, 120*i); // horizontal lines
	xw.drawLine(180, 0, 180, 120*row); // first long vertical line
        for (int j = 2; j < size%5+1; ++j) xw.drawLine(180*j, 120, 180*j, 120*row); // middle vertical lines
	if (size%5 == 0) { for (int k = 2; k < col; ++k) xw.drawLine(180*k, 120, 180*k, 120*row); } 
	else { for (int k = size%5+1; k < col; ++k) xw.drawLine(180*k, 120, 180*k, 120*(row-1)); }
        char c;
        std::cin >> c;
}


void display_hand(std::vector<Card> hand) {
	int size = hand.size();
	std::string name;
	std::string desc;
	int line, length;
	bool lrBoxes = false;
	if (size == 0) {
		Xwindow xw(0, 0);
		char c;
        	std::cin >> c;
		return;
	}
	Xwindow xw(size*180, 120);
	Cardtype ct{};
	std::pair<Type, int> p;
	
	for (int i = 0; i < size; ++i) {
		name = hand.at(i).getName();
		p = ct.construct(name);
		if (p.first == Type::Minion) {
			xw.fillRectangle(180*i, 0, 180, 120, Xwindow::Orange); // draw the rectangle
			xw.drawString(130+(180*i), 40, "Minion");
                        xw.drawString(10+(180*i), 110, std::to_string(hand.at(i).atk)); // attack
                        xw.drawString(160+(180*i), 110, std::to_string(hand.at(i).def)); // defence
                        if (ct.minions.at(p.second).getActivated().getDescription() != "NA") { // actCost
                                xw.drawString(10+(180*i), 65, std::to_string(ct.minions.at(p.second).getActivated().getCost()));
                                xw.drawLine(180*i, 75, 25+(180*i), 75); // horizontal line
                                xw.drawLine(25+(180*i), 45, 25+(180*i), 75); // vertical line
                        }
			lrBoxes = true;

			desc = ct.minions.at(p.second).getActivated().getDescription();
			if (desc == "NA") { // description
				desc = ct.minions.at(p.second).getTriggered().getDescription();
                		if (desc == "NA") desc = "";
                		line = 0;
                		length = desc.length();
                		for (int k = 0; k < length; ++k) {
					int len = ((length - k) < 25) ? (length-k) : 25;
                        		xw.drawString(10+(180*i), 60 + (14*line), desc.substr(k, len));
                        		k += (len-1);
                        		++line;
                		}
			} else {
				line = 0;
                		length = desc.length();
                		for (int j = 0; j < length; ++j) {
					int len = ((length - j) < 22) ? (length-j) : 22;
                        		xw.drawString(35+(180*i), 65 + (15*line), desc.substr(j, len));
                        		j += (len-1);
                        		++line;
                		}
        		}
		} else if (p.first == Type::Enchantment) {
			xw.fillRectangle(180*i, 0, 180, 120, Xwindow::Yellow); // draw the rectangle
                        xw.drawString(130+(180*i), 40, "Enchantment");

                        desc = ct.enchantments.at(p.second).getDes();
                        line = 0;
                        length = desc.length();
                        for (int j = 0; j < length; ++j) { // description
                                int len = ((length - j) < 25) ? (length-j) : 25;
                                xw.drawString(10+(180*j), 65 + (15*line), desc.substr(j, len));
                                j += (len-1);
                                ++line;
                        }

                        if (name == "Giant Strength") {
                                xw.drawString(10+(180*i), 110, "+2");
                                xw.drawString(160+(180*i), 110, "+2");
                        } else if (name == "Enrage") {
                                xw.drawString(10+(180*i), 110, "*2");
                                xw.drawString(160+(180*i), 110, "*2");
                        }
                        if ((name == "Giant Strength") || (name == "Enrage")) lrBoxes = true;

		} else if (p.first == Type::Spell) {
			xw.fillRectangle(180*i, 0, 180, 120, Xwindow::Green); // draw the rectangle
			xw.drawString(130+(180*i), 40, "Spell");
			desc = ct.spells.at(p.second).getDescription();
                        line = 0;
                        length = desc.length();
                        for (int j = 0; j < length; ++j) { // description
                                int len = ((length - j) < 25) ? (length-j) : 25;
                                xw.drawString(10+(180*i), 65 + (15*line), desc.substr(j, len));
                                j += (len-1);
                                ++line;
                        }

		} else if (p.first == Type::Ritual) {
			xw.fillRectangle(180*i, 0, 180, 120, Xwindow::Brown); // draw the rectangle
			xw.drawString(130+(180*i), 40, "Ritual");
                        xw.drawString(10+(180*i), 65, std::to_string(ct.rituals.at(p.second).getActCost())); // actCost
                        xw.drawString(160+(180*i), 110, std::to_string(ct.rituals.at(p.second).getCharge())); // charge

                        xw.drawLine(180*i, 75, 25+(180*i), 75); // left box horizontal line
                        xw.drawLine(25+(180*i), 45, 25+(180*i), 75); // left box vertical line
                        xw.drawLine(145+(180*i), 90, 180+(180*i), 90); // right box horizontal line
                        xw.drawLine(145+(180*i), 90, 145+(180*i), 120); // right box vertical line

			desc = ct.rituals.at(p.second).getDescription();
                	line = 0;
                	length = desc.length();
                	for (int j = 0; j < length; ++j) {
                        	int len = ((length - j) < 22) ? (length-j) : 22;
                        	xw.drawString(35+(180*i), 65 + (15*line), desc.substr(j, len));
                        	j += (len-1);
                        	++line;
                	}

		} else if (p.first == Type::NA) {
			std::cout << "Card " << name << "does not exist in Cardtype, show as blank.";
		}

		if (lrBoxes == true) {
			xw.drawLine(180*i, 90, 30+(180*i), 90); // left box horizontal line
                        xw.drawLine(30+(180*i), 90, 30+(180*i), 120); // left box vertical line
                        xw.drawLine(145+(180*i), 90, 180+(180*i), 90); // right box horizontal line
                        xw.drawLine(145+(180*i), 90, 145+(180*i), 120); // right box vertical line
			lrBoxes = false;
		}

		xw.drawString(10+180*i, 20, name); // name
		xw.drawString(160+(180*i), 20, std::to_string(hand.at(i).getCost()));// cost
		xw.drawLine(180*i, 25, 180+(180*i), 25); // first horizontal line
                xw.drawLine(180*i, 45, 180+(180*i), 45); // second horizontal line
                xw.drawLine(140+(180*i), 0, 140+(180*i), 25); // upper right vertical line
	}

	// draw boarders
	for (int z = 1; z < size; ++z) xw.drawLine(180*z, 0, 180*z, 120);

	char c;
        std::cin >> c;
}

void display_board(Player player1, Player player2) {
	Xwindow xw(900, 580);
	std::string name;
	std::string desc;
	int line;
	int length;
	
	// draw four empty block (White)
	xw.fillRectangle(180, 0, 180, 120, Xwindow::White);
	xw.fillRectangle(540, 0, 180, 120, Xwindow::White);
	xw.fillRectangle(180, 460, 180, 120, Xwindow::White);
	xw.fillRectangle(540, 460, 180, 120, Xwindow::White);
	// draw player1 (Black)
	xw.fillRectangle(360, 0, 180, 120, Xwindow::Black);
	xw.drawString(430, 50, player1.getName(), Xwindow::White); // name
	xw.drawString(370, 110, std::to_string(player1.getHp()), Xwindow::White); // hp
	xw.drawString(520, 110, std::to_string(player1.getMagic()), Xwindow::White); // magic
	// draw player2 (Black)
	xw.fillRectangle(360, 460, 180, 120, Xwindow::Black);
        xw.drawString(430, 530, player2.getName(), Xwindow::White); // name
        xw.drawString(370, 480, std::to_string(player2.getHp()), Xwindow::White); // hp
        xw.drawString(520, 480, std::to_string(player2.getMagic()), Xwindow::White); // magic
	// draw "Sorcery" middle ground
	xw.fillRectangle(0, 240, 900, 100, Xwindow::Black);
	xw.drawBigString(305, 305, "SORCERY", Xwindow::White);

	//draw Ritual of Player1 (Brown)
        xw.fillRectangle(0, 0, 180, 120, Xwindow::Brown);
        if (!(player1.getRitual().empty())) {
                desc = player1.getRitual().at(0).getDescription();
                line = 0;
		length = desc.length();
		for (int i = 0; i < length; ++i) {
                        int len = ((length - i) < 22) ? (length-i) : 22;
                        xw.drawString(35, 65 + (15*line), desc.substr(i, len));
                        i += (len-1);
			++line;
                }

                xw.drawString(130, 40, "Ritual");
                xw.drawString(10, 20, player1.getRitual().at(0).getName()); // name
                xw.drawString(160, 20, std::to_string(player1.getRitual().at(0).getCost())); // cost
                xw.drawString(10, 65, std::to_string(player1.getRitual().at(0).getActCost())); // actCost
                xw.drawString(160, 110, std::to_string(player1.getRitual().at(0).getCharge())); // charge
		
                xw.drawLine(0, 25, 180, 25); // first horizontal line
                xw.drawLine(0, 45, 180, 45); // second horizontal line
                xw.drawLine(140, 0, 140, 25); // upper right vertical line

                xw.drawLine(0, 75, 25, 75); // left box horizontal line
                xw.drawLine(25, 45, 25, 75); // left box vertical line
                xw.drawLine(145, 90, 180, 90); // right box horizontal line
                xw.drawLine(145, 90, 145, 120); // right box vertical line
        }
	//draw Ritual of Player2 (Brown)
        xw.fillRectangle(0, 460, 180, 120, Xwindow::Brown);
        if (!(player2.getRitual().empty())) {
                desc = player2.getRitual().at(0).getDescription();
		line = 0;
		length = desc.length();
                for (int i = 0; i < length; ++i) {
                        int len = ((length - i) < 22) ? (length-i) : 22;
                        xw.drawString(35, 525 + (15*line), desc.substr(i, len));
                        i += (len-1);
			++line;
                }

                xw.drawString(130, 500, "Ritual");
                xw.drawString(10, 480, player2.getRitual().at(0).getName()); // name
                xw.drawString(160, 480, std::to_string(player2.getRitual().at(0).getCost())); // cost
                xw.drawString(10, 525, std::to_string(player2.getRitual().at(0).getActCost())); // actCost
                xw.drawString(160, 570, std::to_string(player2.getRitual().at(0).getCharge())); // charge

                xw.drawLine(0, 485, 180, 485); // first horizontal line
                xw.drawLine(0, 505, 180, 505); // second horizontal line
                xw.drawLine(140, 460, 140, 485); // upper right vertical line

                xw.drawLine(0, 535, 25, 535); // left box horizontal line
                xw.drawLine(25, 505, 25, 535); // left box vertical line
                xw.drawLine(145, 550, 180, 550); // right box horizontal line
                xw.drawLine(145, 550, 145, 580); // right box vertical line
        }

	// draw first card of graveyard of player1 (Orange)
	xw.fillRectangle(720, 0, 180, 120, Xwindow::Orange);
	if (!(player1.getGy().empty())) {
		desc = player1.getGy().at(0).getActivated().getDescription();
		if (desc == "NA") {
			desc = player1.getGy().at(0).getTriggered().getDescription();
			if (desc == "NA") desc = "";
			line = 0;
			length = desc.length();
			for (int i = 0; i < length; ++i) {
				int len = ((length - i) < 25) ? (length-i) : 25;
				xw.drawString(730, 60 + (14*line), desc.substr(i, len));
				i += (len-1);
				++line;
			}
		} else {
			line = 0;
			length = desc.length();
			for (int i = 0; i < length; ++i) {
				int len = ((length - i) < 22) ? (length-i) : 22;
				xw.drawString(755, 65 + (15*line), desc.substr(i, len));
				i += (len-1);
				++line;
			}
		}

		xw.drawString(850, 40, "Minion");
		xw.drawString(730, 20, player1.getGy().at(0).getName()); // name
		xw.drawString(880, 20, std::to_string(player1.getGy().at(0).getCost())); // cost
		xw.drawString(730, 110, std::to_string(player1.getGy().at(0).atk)); // attack
		xw.drawString(880, 110, std::to_string(player1.getGy().at(0).def)); // defence
		if (player1.getGy().at(0).getActivated().getDescription() != "NA") { // actCost
			xw.drawString(730, 65, std::to_string(player1.getGy().at(0).getCost()));
			xw.drawLine(720, 75, 745, 75); // horizontal line
                        xw.drawLine(745, 45, 745, 75); // vertical line
		}
		xw.drawLine(720, 25, 900, 25); // first horizontal line
                xw.drawLine(720, 45, 900, 45); // second horizontal line
                xw.drawLine(860, 0, 860, 25); // upper right vertical line

		xw.drawLine(720, 90, 750, 90); // left box horizontal line
                xw.drawLine(750, 90, 750, 120); // left box vertical line
		xw.drawLine(865, 90, 900, 90); // right box horizontal line
                xw.drawLine(865, 90, 865, 120); // right box vertical line
	}
	// draw first card of graveyard of player2 (Orange)
        xw.fillRectangle(720, 460, 180, 120, Xwindow::Orange);
        if (!(player2.getGy().empty())) {
                desc = player2.getGy().at(0).getActivated().getDescription();
                if (desc == "NA") {
                        desc = player2.getGy().at(0).getTriggered().getDescription();
                        if (desc == "NA") desc = "";
			line = 0;
			length = desc.length();
                        for (int i = 0; i < length; ++i) {
                                int len = ((length - i) < 25) ? (length-i) : 25;
                                xw.drawString(730, 520 + (14*line), desc.substr(i, len));
                                i += (len-1);
				++line;
                        }
                } else {
			line = 0;
			length = desc.length();
                        for (int i = 0; i < length; ++i) {
                                int len = ((length - i) < 22) ? (length-i) : 22;
                                xw.drawString(755, 525 + (15*line), desc.substr(i, len));
                                i += (len-1);
				++line;
                        }
                }

                xw.drawString(850, 500, "Minion");
                xw.drawString(730, 480, player2.getGy().at(0).getName()); // name
                xw.drawString(880, 480, std::to_string(player2.getGy().at(0).getCost())); // cost
                xw.drawString(730, 570, std::to_string(player2.getGy().at(0).atk)); // attack
                xw.drawString(880, 570, std::to_string(player2.getGy().at(0).def)); // defence
                if (player2.getGy().at(0).getActivated().getDescription() != "NA") { // actCost
                        xw.drawString(730, 525, std::to_string(player2.getGy().at(0).getCost()));
			xw.drawLine(720, 535, 745, 535); // left box horizontal line
			xw.drawLine(745, 505, 745, 535); // left box vertical line
                }
                xw.drawLine(0, 485, 180, 485); // first horizontal line
                xw.drawLine(0, 505, 180, 505); // horizontal line
                xw.drawLine(140, 460, 140, 485); // vertical line

                xw.drawLine(720, 550, 750, 550); // left box horizontal line
                xw.drawLine(750, 550, 750, 580); // left box vertical line
                xw.drawLine(865, 550, 900, 550); // right box horizontal line
                xw.drawLine(865, 550, 865, 580); // right box vertical line
        }

	int size;
	// draw player1's board minions
	size = player1.getBoard().size();
	for (int a = 0; a < size; ++a) {
		xw.fillRectangle(180*a, 120, 180, 120, Xwindow::Orange);
		desc = player1.getBoard().at(a).getActivated().getDescription();
                if (desc == "NA") {
                        desc = player1.getBoard().at(a).getTriggered().getDescription();
                        if (desc == "NA") desc = "";
			line = 0;
			length = desc.length();
                        for (int i = 0; i < length; ++i) {
                                int len = ((length - i) < 25) ? (length-i) : 25;
                                xw.drawString(10 + (180*a), 180 + (14*line), desc.substr(i, len));
                                i += (len-1);
				++line;
                        }
                } else {
			line = 0;
			length = desc.length();
                        for (int j = 0; j < length; ++j) {
                                int len = ((length - j) < 22) ? (length-j) : 22;
                                xw.drawString(35 + (180*a), 185 + (15*line), desc.substr(j, len));
                                j += (len-1);
				++line;
                        }
                }

                xw.drawString(130+(180*a), 160, "Minion");
                xw.drawString(10+(180*a), 140, player1.getBoard().at(a).getName()); // name
                xw.drawString(160+(180*a), 140, std::to_string(player1.getBoard().at(a).getCost())); // cost
                xw.drawString(10+(180*a), 230, std::to_string(player1.getBoard().at(a).atk)); // attack
                xw.drawString(160+(180*a), 230, std::to_string(player1.getBoard().at(a).def)); // defence
                if (player1.getBoard().at(a).getActivated().getDescription() != "NA") { // actCost
                        xw.drawString(10+(180*a), 185, std::to_string(player1.getBoard().at(a).getCost()));
			xw.drawLine(180*a, 195, 25+(180*a), 195); // horizontal line
			xw.drawLine(25+(180*a), 165, 25+(180*a), 195); // vertical line
                }
                xw.drawLine(180*a, 145, 180+(180*a), 145); // first horizontal line
                xw.drawLine(180*a, 165, 180+(180*a), 165); // second horizontal line
                xw.drawLine(140+(180*a), 120, 140+(180*a), 145); // upper right vertical line

                xw.drawLine(180*a, 210, 30+(180*a), 210); // left box horizontal line
                xw.drawLine(30+(180*a), 210, 30+(180*a), 240); // left box vertical line
                xw.drawLine(145+(180*a), 210, 180+(180*a), 210); // right box horizontal line
                xw.drawLine(145+(180*a), 210, 145+(180*a), 240); // right box vertical line
	}
	// draw player2's board minions
	size = player2.getBoard().size();
        for (int a = 0; a < size; ++a) {
                xw.fillRectangle(180*a, 340, 180, 120, Xwindow::Orange);
                desc = player2.getBoard().at(a).getActivated().getDescription();
                if (desc == "NA") {
                        desc = player2.getBoard().at(a).getTriggered().getDescription();
                        if (desc == "NA") desc = "";
			line = 0;
			length = desc.length();
                        for (int i = 0; i < length; ++i) {
                                int len = ((length - i) < 25) ? (length-i) : 25;
                                xw.drawString(10 + (180*a), 400 + (14*line), desc.substr(i, len));
                                i += (len-1);
				++line;
                        }
                } else {
			line = 0;
			length = desc.length();
                        for (int j = 0; j < length; ++j) {
                                int len = ((length - j) < 22) ? (length-j) : 22;
                                xw.drawString(35 + (180*a), 405 + (15*line), desc.substr(j, len));
                                j += (len-1);
				++line;
                        }
                }

                xw.drawString(130+(180*a), 380, "Minion");
                xw.drawString(10+(180*a), 360, player2.getBoard().at(a).getName()); // name
                xw.drawString(160+(180*a), 360, std::to_string(player2.getBoard().at(a).getCost())); // cost
                xw.drawString(10+(180*a), 450, std::to_string(player2.getBoard().at(a).atk)); // attack
                xw.drawString(160+(180*a), 450, std::to_string(player2.getBoard().at(a).def)); // defence
                if (player2.getBoard().at(a).getActivated().getDescription() != "NA") { // actCost
                        xw.drawString(10+(180*a), 405, std::to_string(player2.getBoard().at(a).getCost()));
                        xw.drawLine(180*a, 415, 25+(180*a), 415); // horizontal line
                        xw.drawLine(25+(180*a), 385, 25+(180*a), 415); // vertical line
                }
                xw.drawLine(180*a, 365, 180+(180*a), 365); // first horizontal line
                xw.drawLine(180*a, 385, 180+(180*a), 385); // second horizontal line
                xw.drawLine(140+(180*a), 340, 140+(180*a), 365); // upper right vertical line

                xw.drawLine(180*a, 430, 30+(180*a), 430); // left box horizontal line
                xw.drawLine(30+(180*a), 430, 30+(180*a), 460); // left box vertical line
                xw.drawLine(145+(180*a), 430, 180+(180*a), 430); // right box horizontal line
                xw.drawLine(145+(180*a), 430, 145+(180*a), 460); // right box vertical line
        }
	// draw boarders
        xw.drawLine(0, 120, 900, 120);
        xw.drawLine(0, 460, 900, 460);
        for (int i = 0; i < 4; ++i) xw.drawLine(180+(180*i), 0, 180+(180*i), 240);
        for (int j = 0; j < 4; ++j) xw.drawLine(180+(180*j), 340, 180+(180*j), 580);
	char c;
	std::cin >> c;
}
