
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;


vector<int> generateWinningNums() {
    vector<int> randomNums;

    while (randomNums.size() < 7) {
        int newNum = (rand() % 45) + 1;

        // Check if the number already exists in the vector
        bool exists = false;
        for (int num : randomNums) {
            if (num == newNum) {
                exists = true;
                break;
            }
        }

        // Only add the number if it doesn't already exist
        if (!exists) {
            randomNums.push_back(newNum);
        }
    }

    return randomNums;
}


// Function to generate 6 random numbers for user ticket
vector<int> generateUserNums(){
    vector <int> userNums;
    
    for (int i = 0; i < 6; i++) {
        // Get a new random number
		int newNum = ((rand() % 45) + 1);

		// Iterate through the vector to check if the number is already in the vector
		for (int j = 0; j < userNums.size(); j++) {
			if (newNum == userNums[j]) {
				// If it is, get a new number
				newNum = ((rand() % 45) + 1);

				// Reset the loop to check the new number
				j = 0;
			}
		}

		// Add the new number to the vector
        userNums.push_back(newNum);
    }

    return userNums;
}



// Check how many numbers match the winning numbers
double howManyNumbersMatch(vector<int> userNums, vector<int> winningNums)
{
	// Check if any of the user numbers match the winning numbers
	double count = 0;
	int bonusNumber = winningNums[6];

        // first check if there is a bonus number
	    for (int k = 0; k <= 5; k++) {
		    if (userNums[k] == bonusNumber) {
			    count += 0.5;
		    }
        }
		// Check main numbers (order does not matter)
		for (int i = 0; i <= 5; i++) {
			for (int j = 0; j <= 5; j++) {
				if (userNums[i] == winningNums[j]) {
					count++;
				}
			}
		}

		return count;
	}

	
// Check how many numbers match the winning numbers in a row for encore
int howManyNumbersMatchInEncore(vector<int> userNums, vector<int> winningNums) {
	int numMatches = 0;
	int highestMatches = 0;

    for (int i = 0; i < 7; i++) 
    {
		if (userNums[i] == winningNums[i]) 
        {
			// Increment the number of matches in a row
            numMatches++;
		}
        else 
        {

			// Update the highest number of matches if the current number of matches is higher 
            highestMatches = max(highestMatches, numMatches);
            
			// Reset the count if the numbers do not match
			numMatches = 0;
        }
    }
	// One last check to see if the last number was a match
    highestMatches = max(highestMatches, numMatches);

	return highestMatches;
}

void createResultsFile(vector<int> userNums1, vector<int> userNums2, vector<int> winningNums, double amountWon) {
    
    string fileName = "esults" + to_string(time(0)) + ".txt";

    // Open the file
    ofstream outFile(fileName, ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write header and formatted numbers
    outFile << "===================\n";
    outFile << "  LOTTARIO\n";
    outFile << "===================\n";
    outFile << "Winning Numbers: ";

    for (int i = 0; i < winningNums.size(); i++) {
        outFile << setw(2) << winningNums[i];
        if (i < winningNums.size() - 1) outFile << " - ";
    }

    outFile << "\n===================\n";
    outFile << "Your numbers: ";

    for (int i = 0; i < userNums1.size(); i++) {
        outFile << setw(2) << userNums1[i];
        if (i < userNums1.size() - 1) outFile << " - ";
    }

    outFile << "\n===================\n";

    for (int i = 0; i < userNums2.size(); i++) {
        outFile << setw(2) << userNums2[i];
        if (i < userNums2.size() - 1) outFile << " - ";
    }

    outFile << "\n===================\n";
    outFile << "Amount won: " << amountWon << endl;
    
    outFile.close();
}

void generateUserTicket(vector<int>ticketLine1, vector<int>ticketLine2) {


    ofstream output_file;

    // Add time number to the file name to make it unique
    string fileName = "lotteryTicket" + to_string(time(0)) + ".txt";

    std::ofstream outFile(fileName);


    output_file.open(fileName, ios::app);


    if (output_file.is_open()) {

        output_file << "===================\n";
        output_file << "  LOTTARIO\n";
        output_file << "===================\n";
        output_file << "Your Ticket Numbers: " << endl;

        // Add the ticket numbers to the file
        output_file << "Ticket Line 1: ";
        for (int num : ticketLine1) {
            output_file << num << " ";
        }

        output_file << "\n===================\n";

        output_file << "Ticket Line 2: ";
        for (int num : ticketLine2) {
            output_file << num << " ";
        }

        output_file << "\n===================\n";
    }

    else if (output_file.fail()) {
        cout << "Error opening file" << endl;
    }

    output_file.close();

}

double runGame(vector<int> winningNums, double money){
	// Get the users ticket numbers
    vector<int> ticketLine1 = generateUserNums();
    vector<int> ticketLine2 = generateUserNums();

    double matches;
    

    // Output the users numbers
	cout << "Ticket Line 1 Nums: " << endl;
	for (int num : ticketLine1) {
		cout << num << " ";
	}
    cout << endl;
	cout << "Ticket Line 2 Nums: " << endl;

    for (int num : ticketLine2) {
		cout << num << " ";
    }
	cout << endl;
    
	// Output the winning numbers
	cout << "Winning Numbers: " << endl;
	for (int num : winningNums) {
		cout << num << " ";
	}

	cout << endl;


    // Create the users ticket in a file
    generateUserTicket(ticketLine1, ticketLine2);



    //Determine number of matches by higher count in each ticket line
    if (howManyNumbersMatch(ticketLine1, winningNums) > howManyNumbersMatch(ticketLine2, winningNums)) {
        matches = howManyNumbersMatch(ticketLine1, winningNums);
    } else if (howManyNumbersMatch(ticketLine1, winningNums) < howManyNumbersMatch(ticketLine2, winningNums)) {
        matches = howManyNumbersMatch(ticketLine2, winningNums);
    } else {
        matches = howManyNumbersMatch(ticketLine1, winningNums);
    }

    // If else statements to determine prize and adjust budget
    if (matches >= 6){
        cout << "$250,000.00 Jackpot won" << endl;
        money += 250000;
    } else if (matches >= 5.5){
        cout << "$10,000.00 won" << endl;
        money += 10000;
    } else if (matches >= 5){
        cout << "$500.00 won" << endl;
        money += 500;
    } else if (matches >= 4.5){
        cout << "$30.00 won" << endl;
        money += 30;
    } else if (matches >= 4) {
        cout << "$10.00 won" << endl;
        money += 10;
    } else if (matches >= 3.5) {
        cout << "$5.00 won" << endl;
        money += 5;
    } else if (matches >= 3) {
        cout << "$4.00 won" << endl;
        money += 4;
    } else if (matches != static_cast<int>(matches)) // Checking if bonus was won without any other prizes
    {
        cout << "Bonus play won!" << endl;
		// Re run the game
        runGame(winningNums, money);
    } else {
        cout << "You lost. Try again next time" << endl;
    }

	createResultsFile(ticketLine1, ticketLine2, winningNums, money);




    return money;
}

// Generate 7 random numbers for encore
vector<int> generateEncoreNums() {
	vector <int> randomNums;

	for (int i = 0; i < 7; i++) {
		// Get a new random number
		int newNum = ((rand() % 45) + 1);

		// Iterate through the vector to check if the number is already in the vector
		for (int j = 0; j < randomNums.size(); j++) {
			if (newNum == randomNums[j]) {
				// If it is, get a new number
				newNum = ((rand() % 45) + 1);

				// Reset the loop to check the new number
				j = 0;
			}
		}
		randomNums.push_back(newNum);
	}


	return randomNums;
}


double playEncore(double money, int howManyEncores)
{
    // Get the 7 winning numbers
    vector<int> winningNums = generateWinningNums();

    cout << "Winning Encore Numbers: " << endl;
    for (int num : winningNums) {
		cout << num << " ";
    }

	cout << endl;

    for (int i = 0; i < howManyEncores; i++){
        // Get the users ticket numbers
        vector<int> ticketLine1 = generateEncoreNums();

        cout << "Encore ticket Numbers: " << endl;
		for (int num : ticketLine1) {
			cout << num << " ";
		}

		cout << endl;


        // Get the number of matches
        int encoreMatches = howManyNumbersMatchInEncore(ticketLine1, winningNums);

        // Determine the prize
        if (encoreMatches == 7) {
            cout << "Encore Jackpot won!" << endl;
            money += 1000000;
        }
        else if (encoreMatches == 6) {
            cout << "Encore 6/7 won!" << endl;
            money += 100000;
        }
        else if (encoreMatches == 5) {
            cout << "Encore 5/7 won!" << endl;
            money += 10000;
        }
        else if (encoreMatches == 4) {
            cout << "Encore 4/7 won!" << endl;
            money += 1000;
        }
        else if (encoreMatches == 3) {
            cout << "Encore 3/7 won!" << endl;
            money += 100;
        }
        else if (encoreMatches == 2) {
            cout << "Encore 2/7 won!" << endl;
            money += 10;
        }
        else if (encoreMatches == 1) {
            cout << "Encore 1/7 won!" << endl;
            money += 5;
        }
        else {
            cout << "Encore lost!" << endl;
        }
    }
	return money;

}




int main()
{
	// Seed the random number generator
	bool iSeeded = false;
	if (!iSeeded) {
		srand(time(NULL));
		iSeeded = true;
	}


  
    double budget;
	bool isEncore = false;
    int howManyEncores;

    //welcome the user, introduce the rules.
    cout << "Welcome to the Lottery Game!" << endl;
    cout << "https://www.olg.ca/en/lottery/play-lottario-encore/past-results.html view the rules and regulations here." << endl;
    cout << "In this Lottery Game, You get 6 numbers, plus 1 bonus number. Every player gets two lines." << endl;
    cout << "1$ is the price to play 1 game." << endl;
    // Get the users budget to play with
    cout << "Please enter your budget:" << endl;
    cin >> budget;

    while (cin.fail() || budget <= 0) {
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Please enter a positive number for your budget:" << endl;
        cin >> budget;
    }
    
    

    while (true) {
        // Get the winning numbers
        vector<int> nums = generateWinningNums();

		string startGame;
        if (budget >= 1) 
        {
            cout << "Budget: " << budget << "$ | Would you like to purchase a ticket? (y/n)" << endl;
            cin >> startGame;
            //Input validation for startgame
            while (startGame != "n" && startGame != "N" && startGame != "y" && startGame != "Y") {
                cout << "please enter either Y or N" << endl;
                cin >> startGame;
            }

			// Exit the game if the user does not want to play
            if (startGame == "n" || startGame == "N") 
            {
				cout << "Goodbye!" << endl;
                break;
            } else 
            {
                budget -= 1;
				
					cout << "Would you like to play encore? (y/n)" << endl;
					cin >> startGame;
                    while (startGame != "n" && startGame != "N" && startGame != "y" && startGame != "Y") {
                        cout << "please enter either Y or N" << endl;
                        cin >> startGame;
                    }
					if (startGame == "y" || startGame == "Y")
                    {
						// Getting total amount of encore tickets
                         cout << "How many encore tickets would you like? (1-10)" << endl;
                         cin >> howManyEncores;

                         // // Input validation for how many encore tickets
                         while (cin.fail() || !(howManyEncores > 0 && howManyEncores <= 10) || (budget - howManyEncores) < 0) {
                             cin.clear();  
                             cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                             cout << "Please enter a number between 1 and 10 and a number within your budget:" << endl;
                             cin >> howManyEncores;
                         }

						budget -= howManyEncores;
                        double totalMoney = 0;
 
                        totalMoney = playEncore(totalMoney, howManyEncores);
                        budget += totalMoney;
						cout << "Total money made from encore: " << totalMoney << endl;
					}
				
               
                budget = runGame(nums, budget);
            }
        } 
        else
        {
            cout << "You're out of money!" << endl;
			cout << "Goodbye!" << endl;
            break; // End game when out of money
        }
    }

}


