import java.util.Random;

/**
 * Created by shiyi on 16/3/14.
 */
public class Robot {

    private static ChessBoard chess = ChessBoard.getInstance();
    private Robot() {}
    private static int depth = 1;
    private static int robotColor = chess.BLACK;
    private static Robot robot = new Robot();

    public static Robot getRobot() {
        return robot;
    }

    /* alpha_beta剪枝搜索 */
    public int alpha_betaFind(int depth, int alpha, int beta, int color, int prex, int prey) {

        if(depth >= Robot.depth || 0 != chess.isEnd(prex, prey, color%2+1)) {
//            System.out.printf("%d -- %d\n", chess.reckon(robotColor),
//                    chess.reckon(robotColor%2 + 1));
            int ans = chess.reckon(robotColor) - chess.reckon(robotColor%2 + 1);

            if(depth % 2 == 0)
                ans = -ans;

            return ans;
        }

        for(int x=1; x<=chess.N; x++) {
            for(int y=1; y<=chess.N; y++) {

                if(!chess.isEmpty(x, y))
                    continue;

                chess.makeMove(x, y, color);
                int val = -alpha_betaFind(depth+1, -beta, -alpha, color%2+1, x, y);
                //System.out.printf("````````d = %d,  x=%d, y=%d, %d\n",depth,  x, y, val);
                chess.unMove(x, y);

                if(val >= beta)
                    return beta;

                if(val > alpha)
                    alpha = val;
            }
        }
        return alpha;
    }

    /* 返回AI走法 */
    public int[] getNext(int color) {
        int rel[] = new int[2];
        int ans = -100000000;

        Random random = new Random();

        for(int x=1; x<=chess.N; x++) {
            for(int y=1; y<=chess.N; y++) {

                if(!chess.isEmpty(x, y))
                    continue;

                chess.makeMove(x, y, color);

                int val = -alpha_betaFind(0, -100000000, 100000000, color%2 + 1, x, y);
                //System.out.printf("x=%d, y=%d, val=%d\n", x, y, val);

                int ra = random.nextInt(100);

                if(val > ans || val == ans && ra >= 50) {
                    ans = val;
                    rel[0] = x;
                    rel[1] = y;
                }

                chess.unMove(x, y);
            }
        }
        System.out.println(ans);
        return rel;
    }
}




