import org.junit.jupiter.api.Test;
import java.math.BigInteger;

/*
Take two hex strings, XOR them together, and return the hex version of the XOR'd string
 */

public class hex_xor {

    private String xor(String bin1, String bin2) {
        int i;
        StringBuilder temp;
        if (bin1.length() > bin2.length()) {
            temp = new StringBuilder();
            for (i = 0; i < bin2.length(); i++) {
                if ((bin1.charAt(i) == '1' && bin2.charAt(i) == '0') || (bin2.charAt(i) == '1' && bin1.charAt(i) == '0')) {
                    temp.append("1");
                } else {
                    temp.append("0");
                }
            }
            while (i < bin1.length()) {
                temp.append(bin1.charAt(i));
                i++;
            }
        } else {
            temp = new StringBuilder();
            for (i = 0; i < bin1.length(); i++) {
                if ((bin1.charAt(i) == '1' && bin2.charAt(i) == '0') || (bin2.charAt(i) == '1' && bin1.charAt(i) == '0')) {
                    temp.append("1");
                } else {
                    temp.append("0");
                }
            }
            while (i < bin2.length()) {
                temp.append(bin2.charAt(i));
                i++;
            }
        }
        return temp.toString();
    }

    private String hexToBinary(String hex){
        return (new BigInteger(hex, 16).toString(2));
    }

    private String  binaryToHex(String binary){
        return (new BigInteger(binary, 2).toString(2));
    }

    public String init(String hex1, String hex2) {
        if (hex1.length() < 1 || hex2.length() < 1) {
            return "Please enter a valid string\n";
        }

        String bin1 = hexToBinary(hex1);
        String bin2 = hexToBinary(hex2);
        String temp = xor(bin1, bin2);
        return binaryToHex(temp);
    }

    @Test
    private void test() {
        String out;

        System.out.println("Test 1: running...\n");
        out = init("0", "");
        assert (out.equals("Please enter a valid string\n"));
        System.out.println("Test 1: Passed\n\n");

        System.out.println("Test 2: running...\n");
        out = init("0", "0");
        assert (out.equals("0"));
        System.out.println("Test 2: Passed\n\n");

        System.out.println("Test 3: running...\n");
        out = init("ff", "ff");
        assert (out.equals("0"));
        System.out.println("Test 3: Passed\n\n");

        System.out.println("Test 4: running...\n");
        out = init("666f6f626172", "b789056ab0193");
        assert (out.equals("b1eff39c960e100"));
        System.out.println("Test 4: Passed\n\n");

        System.out.println("Test 5: running...\n");
        out = init("666f6f", "938e89f9a0c9c");
        assert (out.equals("938e89ffc63f3"));
        System.out.println("Test 5: Passed\n\n");

        System.out.println("Test 6: running...\n");
        out = init("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965");
        assert (out.equals("746865206b696420646f6e277420706c6179"));
        System.out.println("Test 6: Passed\n\n");

        System.exit(0);
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("\n***************************************************\n");
            System.out.println("Usage: java hex_xor < -t > | < hex_string> <hex_string> \n");
            System.out.println("*****************************************************\n\n");
            return;
        }

        hex_xor h = new hex_xor();

        if (args[0].equals("-d")) {
            System.out.println(h.init("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", "00ff"));
            return;
        }

        if (args[0].equals("-t")) {
            //tests
            h.test();
        }

        String hex1 = args[1];
        String hex2 = args[2];
        System.out.println(h.init(hex1, hex2));
    }
}
