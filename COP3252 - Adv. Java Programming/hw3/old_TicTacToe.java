public class tictactoe {
    public static void main(String args[]){

        // Check for any arguments
        switch (args.length) {
            case 0:
                
                break;
            case 1:
                if(args[0] != "-c"){
                    System.out.println("Argument not found. Please use one of the following:");
                    System.out.println("\tjava TicTacToe\t\ttwo human players");
                    System.out.println("\tjava TicTacToe -c\ttwo computer players");
                    System.out.println("\tjava TicTacToe -c 1\tcomputer is player 1, human player 2");
                    System.out.println("\tjava TicTacToe -c 2\thuman player 1, computer player 2");
                    System.exit(0);
                }
            default:
                break;
        }

        System.out.println("Welcome to the simulation. Enjoy your stay!");
        Gameboard game = new Gameboard();
        System.out.println(game + "\n\n");
        game.showPositions();
    }
}

class Gameboard{
    int[] board = new int[9];
    boolean GameOver = false;
    boolean Tie = false;
    String EndCredit;

    public Gameboard(){
        for(int i = 0; i < 9; i++){
            this.board[i] = 0;
        }
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
    
    public String toString(){
        StringBuilder sb = new StringBuilder(50);
        for(int i = 1; i < 10; i++){
            if(i % 3 != 0){
                if(board[i-1] == 2)
                    sb.append(" O |");
                else if (board[i-1] == 1)
                    sb.append(" X |");
                else
                    sb.append("   |");
            }
            else if(i % 3 == 0 && i != 9){
                if(board[i-1] == 2)
                    sb.append(" O \n-----------\n");
                else if (board[i-1] == 1)
                    sb.append(" X \n-----------\n");
                else
                    sb.append("   \n-----------\n");
            }
            else{
                if(board[i-1] == 2)
                    sb.append(" O ");
                else if (board[i-1] == 1)
                    sb.append(" X ");
                else
                    sb.append("   ");
            }
        }
        return sb.toString();
    }

    private void BoardCheck(){
        // Check for 3 in a row - Then a Winner
        
        // Check all winning combos related to Position 5
        // (159, 258, 357, 456)
        if(board[5] != 0){
            // 159
            if(board[5] == board[1]){
                if(board[5] == board[9]){
                    this.GameOver = true;
                }
            }
            // 258
            if(board[5] == board[2]){
                if(board[5] == board[8]){
                    this.GameOver = true;
                }
            }
            // 357
            if(board[5] == board[3]){
                if(board[5] == board[7]){
                    this.GameOver = true;
                }
            }

            // 456
            if(board[5] == board[4]){
                if(board[5] == board[6]){
                    this.GameOver = true;
                }
            }
        }

        // Check all combos relating to Position 1
        // (147, 123)
        if(board[1] != 0){
            // 147
            if(board[1] == board[4]){
                if(board[1] == board[7]){
                    this.GameOver = true;
                }
            }
            // 123
            if(board[1] == board[2]){
                if(board[1] == board[3]){
                    this.GameOver = true;
                }
            }
        }

        // Check all combos relating to Position 9
        // (789, 369)
        if(board[9] != 0){
            // 789
            if(board[9] == board[8]){
                if(board[9] == board[7]){
                    this.GameOver = true;
                }
            }
            // 369
            if(board[9] == board[6]){
                if(board[9] == board[3]){
                    this.GameOver = true;
                }
            }
        }

        // Check for full board - then a Tie
        for(int pos : this.board){
            if(pos == 0)
                break;
        }
        this.GameOver = true;
        this.Tie = true;
    }

}


class Player{
    String name;
    char blotter;

    public Player(){

    }
}

class User extends Player{
    public User(){

    }
}

class Computer extends Player{
    public Computer(){

    }

    private int NextMove(int[] board){
        if(CheckWin(board) != 0)
            return CheckWin(board);
        else if (CheckLoss(board) != 0)
            return CheckLoss(board);
        else{
            return 0;
        }
    }
    
    // 123, 456, 789, 147, 258, 369, 159, 359
    private int CheckWin(int[] board){
        // Go through and check for potential winning moves
        // Place move there and conquer your opponent
        if(board[5] != 0){
            if(board[1] == board[5]){
                if(board[9] == board[5])
                    return -1;
                
            }
        }


        return 0;
    }

    private int CheckLoss(int[] board){
        // Go through and check for potential losing moves
        // Place move there
        return 0;
    }

}