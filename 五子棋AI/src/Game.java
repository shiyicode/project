import java.util.Scanner;

/**
 * Created by shiyi on 16/3/14.
 */
//public class Game {
//
//    private static boolean flag = false;
//    private ChessBoard chess = ChessBoard.getInstance();
//    private int userColor = chess.WHITE;
//    private int robotColor = chess.BLACK;
//
//    public void makeMove(int x, int y, int color) {
//        chess.makeMove(x, y, color);
//    }
//
//    public void start() {
//
//        Robot robot = Robot.getRobot();
//        int rel = 0;
//
//        makeMove(chess.N/2+1, chess.N/2+1, chess.BLACK);
//
//        while(true) {
//
//
//            makeMove(user[0], user[1], userColor);
//            rel = chess.isEnd(user[0], user[1], userColor);
//            if(rel != 0)
//                break;
//
//            int rob[] = robot.getNext(robotColor);
//            System.out.printf("R  %d----%d\n", rob[0], rob[1]);
//            makeMove(rob[0], rob[1], robotColor);
//            rel = chess.isEnd(rob[0], rob[1], robotColor);
//            if(rel != 0)
//                break;
//        }
//
//        if(rel == userColor)
//            System.out.println("玩家胜");
//        else
//            System.out.println("机器胜");
//    }
//}
