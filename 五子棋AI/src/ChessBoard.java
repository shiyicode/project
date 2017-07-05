/**
 * Created by shiyi on 16/3/14.
 */
public class ChessBoard {
    public final int N = 15;
    public final int EMPTY = 0;
    public final int BLACK = 1;
    public final int WHITE = 2;

    public int[][] board = new int[N+1][N+1];

    private ChessBoard() {}
    private static final ChessBoard chess = new ChessBoard();

    /* 返回类单例 */
    public static ChessBoard getInstance() {
        return chess;
    }

    /*  判断该位置是否无子 */
    public boolean isEmpty(int x, int y) {
        return board[x][y] == EMPTY;
    }

    /* 落子 */
    public void makeMove(int x, int y, int color) {
        board[x][y] = color;
    }

    /* 撤子 */
    public void unMove(int x, int y) {
        board[x][y] = EMPTY;
    }

    public int reckon(int color) {

        int dx[] = {1, 0, 1, 1};
        int dy[] = {0, 1, 1, -1};
       // System.out.printf("00000==%d\n", color);
        int ans = 0;

        for(int x=1; x<=N; x++) {
            for (int y = 1; y <= N; y++) {
                if (board[x][y] != color)
                    continue;

                int num[][] = new int[2][100];

                for (int i = 0; i < 4; i++) {
                    int sum = 1;
                    int flag1 = 0, flag2 = 0;

                    int tx = x + dx[i];
                    int ty = y + dy[i];
                    while (tx > 0 && tx <= N
                            && ty > 0 && ty <= N
                            && board[tx][ty] == color) {
                        tx += dx[i];
                        ty += dy[i];
                        ++sum;
                    }

                    if(tx > 0 && tx <= N
                            && ty > 0 && ty <= N
                            && board[tx][ty] == EMPTY)
                        flag1 = 1;

                    tx = x - dx[i];
                    ty = y - dy[i];
                    while (tx > 0 && tx <= N
                            && ty > 0 && ty <= N
                            && board[tx][ty] == color) {
                        tx -= dx[i];
                        ty -= dy[i];
                        ++sum;
                    }

                    if(tx > 0 && tx <= N
                            && ty > 0 && ty <= N
                            && board[tx][ty] == EMPTY)
                        flag2 = 1;

                    if(flag1 + flag2 > 0)
                        ++num[flag1 + flag2 - 1][sum];
                }

                //成5⃣
                if(num[0][5] + num[1][5] > 0)
                    ans = Math.max(ans, 100000);
                    //活4 | 双死四 | 死4活3
                else if(num[1][4] > 0
                        || num[0][4] > 1
                        || (num[0][4] > 0 && num[1][3] > 0))
                    ans = Math.max(ans, 10000);
                    //双活3
                else if(num[1][3] > 1)
                    ans = Math.max(ans, 5000);
                    //死3活3
                else if(num[1][3] > 0 && num[0][3] > 0)
                    ans = Math.max(ans, 1000);
                    //死4
                else if(num[0][4] > 0)
                    ans = Math.max(ans, 500);
                    //单活3
                else if(num[1][3] > 0)
                    ans = Math.max(ans, 200);
                    //双活2
                else if(num[1][2] > 1)
                    ans = Math.max(ans, 100);
                    //死3
                else if(num[0][3] > 0)
                    ans = Math.max(ans, 50);
                    //双活2
                else if(num[1][2] > 1)
                    ans = Math.max(ans, 10);
                    //单活2
                else if(num[1][2] > 0)
                    ans = Math.max(ans, 5);
                    //死2
                else if(num[0][2] > 0)
                    ans = Math.max(ans, 1);

            }
        }

        return ans;
    }

    /* 判断局面是否结束 0未结束 1WHITE赢 2BLACK赢 */
    public int isEnd(int x, int y, int color) {
        int dx[] = {1, 0, 1, 1};
        int dy[] = {0, 1, 1, -1};

        for (int i = 0; i < 4; i++) {
            int sum = 1;

            int tx = x + dx[i];
            int ty = y + dy[i];
            while (tx > 0 && tx <= N
                    && ty > 0 && ty <= N
                    && board[tx][ty] == color) {
            //    System.out.printf("%d == %d || \n", tx, ty);
                tx += dx[i];
                ty += dy[i];
                ++sum;
            }

            tx = x - dx[i];
            ty = y - dy[i];
            while (tx > 0 && tx <= N
                    && ty > 0 && ty <= N
                    && board[tx][ty] == color) {
               // System.out.printf("%d -- %d || \n", tx, ty);
                tx -= dx[i];
                ty -= dy[i];
                ++sum;
            }

            //System.out.println(sum);

            if(sum >= 5)
                return color;
        }
        return 0;
    }
}
