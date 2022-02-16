/**
 * Tic Tac Toe - The GAME
 * Author: Kaedon Hamm (kah16h)
 * Class: COP 3252 - Advanced Java Programming
 * Due Date: 2/12/2021
 * 
 * Idea was to have 2 different Layers
 * Game - Seen as the "referee", controls/checks Game State, as well as receives Movement Request from a Player and checks if it is a legal move
 * Player - Can create Movement Requests
 *     - User - Asked by Game to send in a Movement Request via Keyboard
 *     - Computer - Generates a Movement Request based upon certain rules stated in Assignment
 * 
 * Game only sees a Requested Number where the way that number is created is dont by the Player
 * 
 * Jar: jar cfe hw3.jar TicTacToe *.class *.java
 * Run: java -jar hw3.jar [-c [1|2]]
 */

import java.util.Random;
import java.util.Scanner;
import javax.lang.model.util.ElementScanner6;   // This was imported automatically for some reason...


public class TicTacToe {
    public static void main(String args[]){

        // Check for any arguments
        if(args.length > 3) {
            argsError();
            System.exit(0);
        }
        // 0 args, 2 Users
        else if(args.length == 0){
            // Game with 2 Human players
            User p1 = new User();
            User p2 = new User();
            Game game = new Game(p1, p2);
            gameloop(game);
        }
        // 1 arg of -c, 2 Computers
        else if(args.length == 1){
            System.out.println(args[0]);
            if(!(args[0].equals("-c"))){
                argsError();
                System.exit(0);
            }
            Computer p1 = new Computer();
            Computer p2 = new Computer();
            Game game = new Game(p1, p2);
            gameloop(game);
        }
        // 2 args, -c 1 || -c 2
        else if(args.length == 2){
            if(args[1].equals("1")){
                // Game with Player 1: Computer; Player 2: Human
                Computer p1 = new Computer();
                User p2 = new User();
                Game game = new Game(p1, p2);
                gameloop(game);
            }
            else if(args[1].equals("2")){
                // Game with Player 1: Human; Player 2: Computer
                User p1 = new User();
                Computer p2 = new Computer();
                Game game = new Game(p1, p2);
                gameloop(game);
            }
            else{
                argsError();
                System.exit(0);
            }
        }
        else{
            argsError();
            System.exit(0);
        }
    }

    // Where entire game is ran. Seperated to remove redundant code.
    private static void gameloop(Game game){
        do{
            int pos = 5;
            // Player 1 goes
            System.out.println(game);
            do{
                System.out.print("Player 1's Turn: ");
                pos = game.p1.requestMove(game.board, 1);
                System.out.println();
            }while(game.moveRequested(pos, 1) == 0);

            // End game if Player 1 wins on their turn
            if(game.Gamestate() != 0)
                break;

            // Player 2 goes
            System.out.println(game);
            do{
                System.out.print("Player 2's Turn: ");
                pos = game.p2.requestMove(game.board, 2);
                System.out.println();
            }while(game.moveRequested(pos, 2) == 0);

        }while(game.Gamestate() == 0);

        // End Screen Messages
        if(game.Gamestate() == 1){
            System.out.println("\n------------------\n| Player 1 Wins! |\n------------------");
        }
        else if(game.Gamestate() == 2){
            System.out.println("\n------------------\n| Player 2 Wins! |\n------------------");
        }
        if(game.Gamestate() == 3){
            System.out.println("\n------------------\n|   It's a Tie!  |\n------------------");
        }
        System.out.println(game);
    };

    // Error statement for misuse of arguments
    private static void argsError(){
        System.out.println("Argument not found. Please use one of the following:");
        System.out.println("\tjava TicTacToe\t\ttwo human players");
        System.out.println("\tjava TicTacToe -c\ttwo computer players");
        System.out.println("\tjava TicTacToe -c 1\tcomputer is player 1, human player 2");
        System.out.println("\tjava TicTacToe -c 2\thuman player 1, computer player 2");
    }
}


// Game holds all information regarding the current session
// Used as a different layer than all Players
class Game{
    int[] board = new int[9];
    int[] openmoves = new int[9];
    int[] positions = new int[9];
    Player p1;
    Player p2;

    public Game(){

        // Fill in gameboard with empty spaces
        for(int i = 0; i < 9; i++){
            this.board[i] = 0;
            this.positions[i] = i;
            this.openmoves[i] = 0;
        }
    }

    public Game(User p1, User p2){

        // Fill in gameboard with empty spaces
        for(int i = 0; i < 9; i++){
            this.board[i] = 0;
            this.positions[i] = i;
            this.openmoves[i] = 0;
        }
        this.p1 = p1;
        this.p2 = p2;
    }

    public Game(Computer p1, Computer p2){

        // Fill in gameboard with empty spaces
        for(int i = 0; i < 9; i++){
            this.board[i] = 0;
            this.positions[i] = i;
            this.openmoves[i] = 0;
        }
        this.p1 = p1;
        this.p2 = p2;
    }

    public Game(User p1, Computer p2){

        // Fill in gameboard with empty spaces
        for(int i = 0; i < 9; i++){
            this.board[i] = 0;
            this.positions[i] = i;
            this.openmoves[i] = 0;
        }
        this.p1 = p1;
        this.p2 = p2;
    }

    public Game(Computer p1, User p2){

        // Fill in gameboard with empty spaces
        for(int i = 0; i < 9; i++){
            this.board[i] = 0;
            this.positions[i] = i;
            this.openmoves[i] = 0;
        }
        this.p1 = p1;
        this.p2 = p2;
    }

    public void assignPlayers(Player p1, Player p2){
        this.p1 = p1;
        this.p2 = p2;
    }

    public void showPositions(){
        StringBuilder sb = new StringBuilder(50);

        for(int i = 1; i < 10; i++){
            if(i % 3 != 0)
                sb.append(" " + i + " |");
            else if(i % 3 == 0 && i != 9)
                sb.append(" " + i + " \n-----------\n");
            else
                sb.append(" " + i + " ");
        }

        System.out.println(sb);
    }

    // Ugly but works to provide Positions board next to current board
    public String toString(){
        StringBuilder sb = new StringBuilder(50);
        System.out.println("Game Board:\t\tPositions:\n");
        for(int i = 1; i < 10; i++){
            if(i % 3 != 0){
                if(this.board[i-1] == 2)
                    sb.append(" O |");
                else if (board[i-1] == 1)
                    sb.append(" X |");
                else
                    sb.append("   |");
            }
            else if(i % 3 == 0 && i != 9){
                if(this.board[i-1] == 2)
                    sb.append(" O \t\t " + (i-2) + " | " + (i-1) +  " | " + i + "\n-----------\t\t-----------\n");
                else if (board[i-1] == 1)
                    sb.append(" X \t\t " + (i-2) + " | " + (i-1) + " | " + i + "\n-----------\t\t-----------\n");
                else
                    sb.append("   \t\t " + (i-2) + " | " + (i-1) + " | " + i + "\n-----------\t\t-----------\n");
            }
            else{
                if(this.board[i-1] == 2)
                    sb.append(" O ");
                else if (board[i-1] == 1)
                    sb.append(" X ");
                else
                    sb.append("   ");
            }
        }
        sb.append("\t\t 7 | 8 | 9\n");
        return sb.toString();
    }

    public int Gamestate(){
        // 0 == Playable state
        // 1 == Winner Player 1
        // 2 == Winner Player 2
        // 3 == Tie, full board

        // Check all winning combos related to Position 5
        // (159, 258, 357, 456)
        if(board[4] != 0){
            // 159
            if(board[4] == board[0]){
                if(board[4] == board[8]){
                    return board[4];
                }
            }
            // 258
            if(board[4] == board[1]){
                if(board[4] == board[7]){
                    return board[4];
                }
            }
            // 357
            if(board[4] == board[2]){
                if(board[4] == board[6]){
                    return board[4];
                }
            }

            // 456
            if(board[4] == board[3]){
                if(board[4] == board[5]){
                    return board[4];
                }
            }
        }

        // Check all combos relating to Position 1
        // (147, 123)
        if(board[0] != 0){
            // 147
            if(board[0] == board[3]){
                if(board[0] == board[6]){
                    return board[0];
                }
            }
            // 123
            if(board[0] == board[1]){
                if(board[0] == board[2]){
                    return board[0];
                }
            }
        }

        // Check all combos relating to Position 9
        // (789, 369)
        if(board[8] != 0){
            // 789
            if(board[8] == board[7]){
                if(board[8] == board[6]){
                    return board[8];
                }
            }
            // 369
            if(board[8] == board[5]){
                if(board[8] == board[2]){
                    return board[8];
                }
            }
        }

        // Check for Open Play
        for(int pos : this.board){
            if(pos == 0){
                return 0;
            }
        }

        // Open play
        return 3;
    }

    public int moveRequested(int pos, int player){
        System.out.println("Player " + player + " Requested " + pos);
        // Retrieves a moveRequest from Player
        if(checkMove(pos, player) == 1){
            System.out.println("Please select an open position.");
            return 0;
        };
        return 1;
    }

    public int checkMove(int pos, int player){
        // Ensures move is legal
        if(this.board[pos-1] == 0){
            executeMove(pos, player);
            return 0;
        }
        return 1;
    }

    public void executeMove(int pos, int player){
        // Fills board with player's blotter number
        this.board[pos-1] = player;
    }
}


// Abstract base class allows for different types of Players and overrides of Movement functions
abstract class Player{
    public abstract int requestMove(int[] gameboard, int player);
}

class User extends Player{
    public User(){
        super();
    }

    public int requestMove(int[] gameboard, int player){
        // Take user input for their next Move and initiate moveRequest with Game
        Scanner input = new Scanner(System.in);
        int pos = input.nextInt();
        return pos;
    }
}

class Computer extends Player{
    int[] board;

    public Computer(){
        super();
    }

    public int requestMove(int[] gameboard, int player){
        // Calculate next move and initiate moveRequest with Game
        if(checkWin(gameboard, player) != -1)
            return checkWin(gameboard, player);
        else if(checkLose(gameboard, player) != -1)
            return checkLose(gameboard, player);
        else if(checkMiddle(gameboard) != -1)
            return 5;
        else
            return randMove(gameboard);
    }

    public int checkWin(int[] board, int player){

        // Rows
        for(int i = 0; i < 9; i += 3){
            if(board[i] == player && board[i+1] == player && board[i+2] == 0){
                return i+3;
            }
            else if (board[i] == player && board[i+2] == player && board[i+1] == 0)
                return i+2;
            else if (board[i+1] == player && board[i+2] == player && board[i] == 0)
                return i+1;
        }

        // Columns
        for(int i = 0; i < 3; i++){
            if(board[i] == player && board[i+3] == player && board[i+6] == 0)
                return i+7;
            else if (board[i] == player && board[i+6] == player && board[i+3] == 0)
                return i+4;
            else if (board[i+3] == player && board[i+6] == player && board[i] == 0)
                return i+1;
        }

        // Diagonal Down Right
        if(board[0] == player && board[4] == player && board[8] == 0)
                return 9;
            else if (board[0] == player && board[8] == player && board[4] == 0)
                return 5;
            else if (board[4] == player && board[8] == player && board[0] == 0)
                return 1;

        // Diagonal Down Left
        if(board[2] == player && board[4] == player && board[6] == 0)
                return 7;
            else if (board[2] == player && board[6] == player && board[4] == 0)
                return 5;
            else if (board[4] == player && board[6] == player && board[2] == 0)
                return 3;
        return -1;
    }

    public int checkLose(int[] board, int player){
        for(int i = 0; i < 9 ; i++)
        if(player == 1)
            return checkWin(board, 2);
        return checkWin(board, 1);
    }

    public int checkMiddle(int[] board){
        if(board[4] == 0)
            return 5;
        return -1;
    }

    public int randMove(int[] board){
        int max = 8;
        int min = 0;
        int range = max - min + 1;
        int rand_pos;
        do{
            rand_pos = (int)(Math.random() * range) + min;
        }while(board[rand_pos] != 0);

        return rand_pos+1;
    }
}