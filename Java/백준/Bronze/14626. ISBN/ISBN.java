import java.io.*;
import java.util.*;

//https://www.acmicpc.net/problem/14626

/*

*/

    
public class Main {

    
    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        String str = st.nextToken();
        int sum = 0;
        int idx = 0;
        for(int i = 0; i < str.length(); i++){
            if(str.charAt(i) == '*'){
                idx = i;
                continue;
            }
            if(i % 2 == 0){
                sum += str.charAt(i) - '0';
            }else{
                sum += (str.charAt(i) - '0') * 3;
            }
        }
        int ans = 0;
        for(int i = 0; i < 10; i++){
             if((sum + i * (idx % 2 == 0 ? 1 : 3)) % 10 == 0){
                ans = i;
                break;
            }
        }
        System.out.println(ans);
    }
}
