import java.io.*;
import java.math.BigInteger;
import java.util.*;
public class Main {
    static BigInteger[] catalan = new BigInteger[500];
    public static void main(String[] args) {
        InputStream fin = null;
        PrintStream fout = null;
        try {
            fin = new FileInputStream("hankel.in");
            fout = new PrintStream(new FileOutputStream("hankel.out"));
        } catch (Exception e) {
            System.exit(1);
        }
        Scanner cin = new Scanner(fin);
        int N = cin.nextInt();
        catalan[0] = BigInteger.ONE;
        catalan[1] = BigInteger.ONE;
        for (int i = 2; i < N; i++) {
            catalan[i] = BigInteger.ZERO;
            for (int j = 0; j < i; j++) {
                catalan[i] = catalan[i].add(catalan[j].multiply(catalan[i - 1 - j]));
            }
        }
        for (int i = 0; i < N; i++) {
            fout.println(catalan[i]);
            if (i != N - 1) fout.println(0);
        }
    }
}
