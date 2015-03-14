import java.io.*;
import java.math.BigInteger;
import java.util.*;
public class Main {
    static int gcd(int x, int y) {
        while (y > 0) {
            int t = x % y;
            x = y; y = t;
        }
        return x;
    }
    public static void main(String[] args) {
        InputStream fin = null;
        PrintStream fout = null;
        try {
            fin = new FileInputStream("clever.in");
            fout = new PrintStream(new FileOutputStream("clever.out"));
        } catch (Exception e) {
            System.exit(1);
        }
        Scanner cin = new Scanner(fin);
        int N = cin.nextInt(), M = cin.nextInt(), K = cin.nextInt();
        BigInteger num = BigInteger.valueOf(M), denom = BigInteger.ONE;
        BigInteger mnum = BigInteger.valueOf(N-2), mdenom = BigInteger.valueOf(N);
        for (int i = 0; i < K; i++) {
            denom = denom.multiply(mdenom);
            num = num.multiply(mnum).add(denom);
        }
        BigInteger g = denom.gcd(num);
        denom = denom.divide(g);
        num = num.divide(g);
        fout.printf("%s/%s\n", num, denom);
    }
}
