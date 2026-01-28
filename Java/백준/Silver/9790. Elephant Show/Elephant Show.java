import java.util.*;

public class Main {
    static int[] dx = {0, 0, 1, -1};
    static int[] dy = {1, -1, 0, 0};

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            int W = sc.nextInt();
            int H = sc.nextInt();

            // W와 H가 0이면 입력 종료
            if (W == 0 && H == 0) break;

            char[][] map = new char[H][W];
            boolean[][] visited = new boolean[H][W];
            int startX = 0, startY = 0;

            // 맵 입력 및 코끼리 위치('A') 찾기
            for (int i = 0; i < H; i++) {
                String line = sc.next();
                for (int j = 0; j < W; j++) {
                    map[i][j] = line.charAt(j);
                    if (map[i][j] == 'A') {
                        startX = i;
                        startY = j;
                    }
                }
            }

            System.out.println(bfs(startX, startY, H, W, map, visited));
        }
    }

    public static int bfs(int x, int y, int H, int W, char[][] map, boolean[][] visited) {
        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{x, y});
        visited[x][y] = true;
        
        int count = 1; // 코끼리가 있는 첫 번째 타일 포함

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();

            for (int i = 0; i < 4; i++) {
                int nx = curr[0] + dx[i];
                int ny = curr[1] + dy[i];

                // 맵 범위 안이고, 방문하지 않았으며, 노란 타일('.')인 경우
                if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
                    if (!visited[nx][ny] && map[nx][ny] == '.') {
                        visited[nx][ny] = true;
                        queue.add(new int[]{nx, ny});
                        count++;
                    }
                }
            }
        }
        return count;
    }
}