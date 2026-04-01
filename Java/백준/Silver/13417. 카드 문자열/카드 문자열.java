import java.util.*;

public class Main {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        if (!sc.hasNextInt()) return;
        
        int T = sc.nextInt();

        for (int i = 0; i < T; i++) {
            int N = sc.nextInt();
            Deque<Character> D = new LinkedList<>();

            for (int j = 0; j < N; j++) {
                char cur = sc.next().charAt(0);
                
                if (D.isEmpty()) {
                    D.addFirst(cur);
                } else {
                    if (cur <= D.peekFirst()) {
                        D.addFirst(cur);
                    } else {
                        D.addLast(cur);
                    }
                }
            }

            StringBuilder sb = new StringBuilder();
            while (!D.isEmpty()) {
                sb.append(D.pollFirst());
            }
            System.out.println(sb.toString());
        }
        sc.close(); 
    }
}