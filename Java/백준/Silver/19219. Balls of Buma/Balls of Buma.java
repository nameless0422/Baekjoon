import java.io.*;
import java.util.*;

//https://www.acmicpc.net/problem/19219

/*

*/

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();

        List<Group> groups = new ArrayList<>();
        if (s.length() > 0) {
            char curChar = s.charAt(0);
            int count = 1;
            for (int i = 1; i < s.length(); i++) {
                if (s.charAt(i) == curChar) {
                    count++;
                } else {
                    groups.add(new Group(curChar, count));
                    curChar = s.charAt(i);
                    count = 1;
                }
            }
            groups.add(new Group(curChar, count));
        }

        int n = groups.size();
        if (n % 2 == 0) {
            System.out.println(0);
            return;
        }

        int mid = n / 2;
        for (int i = 0; i < mid; i++) {
            Group left = groups.get(i);
            Group right = groups.get(n - 1 - i);
            if (left.color != right.color || (left.count + right.count) < 3) {
                System.out.println(0);
                return;
            }
        }

        Group center = groups.get(mid);
        if (center.count >= 2) {
            System.out.println(center.count + 1);
        } else {
            System.out.println(0);
        }
    }

    static class Group {
        char color;
        int count;

        Group(char color, int count) {
            this.color = color;
            this.count = count;
        }
    }
}