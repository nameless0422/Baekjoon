import java.io.*;
import java.util.*;

//https://www.acmicpc.net/problem/3264

/*



5 2           교차로가 5개 시작은 2번
1 2 1         1번-(1)-2번-(2)-3번-(2)-4번-(1)-5번
2 3 2
3 4 2
4 5 1


5 1           교차로가 5개 시작은 1번  
1 2 1         1번-(1)-2번-(1)-3번-(1)-4번
2 3 1                          ㄴ(1)-5번
3 5 1
3 4 1


4 1           교차로 4개 시작 1
1 3 2         1번-(2)-3번
1 2 3           ㄴ(3)-2번
1 4 4           ㄴ(4)-4번

*/

    
public class Main {

    static class Node{
        int to, weight;
        Node(int to, int weight){
            this.to = to;
            this.weight = weight;
        }
    }

    static List<Node>[] adj;
    static long maxDist = 0;
    
    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int S = Integer.parseInt(st.nextToken());

        adj = new ArrayList[N+1];
        for(int i=1; i<=N; i++){
            adj[i] = new ArrayList<>();
        }

        long total = 0;

        for(int i=0; i<N-1; i++){
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());
            adj[a].add(new Node(b, c));
            adj[b].add(new Node(a, c));
            total += c;
        }

        dfs(S,-1,0);

        System.out.println(2 * total - maxDist);   
    }

    static void dfs(int curr, int prev, long dist){
        if(dist > maxDist){
            maxDist = dist;
        }
        for(Node next : adj[curr]){
            if(next.to != prev){
                dfs(next.to, curr, dist + next.weight);
            }            
        }
    }
}
