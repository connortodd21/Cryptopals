public class singleByteXOR {

    private int characterValue(char c){
        switch (c){
            case 'e': return 27; case 't': return 26; case ' ': return 25; case 'a': return 24; case 'o': return 23;
            case 'i': return 22; case 'n': return 21; case 's': return 20; case 'h': return 19; case 'r': return 18;
            case 'd': return 17; case 'l': return 16; case 'c': return 15; case 'u': return 14; case 'm': return 13;
            case 'w': return 12; case 'f': return 11; case 'g': return 10; case 'y': return 9; case 'p': return 8;
            case 'b': return 7; case 'v': return 6; case 'k': return 5; case 'j': return 4; case 'x': return 3;
            case 'q': return 2; case 'z': return 1;
            default: return -10;
        }
    }

    private void init(String hex){
        hex_xor x = new hex_xor();
        for (int i = 0; i < 256; i++) {
            String hexedChar = String.format("%04x", i);
            String xor = x.init(hex, hexedChar);
        }
    }

    private void test(){

    }

    public static void main(String[] args) {
        if(args.length < 1){
            System.out.println("\n************************************************\n");
            System.out.println("Usage: java singleByteXOR < -t > | < hex_string> \n");
            System.out.println("************************************************\n\n");
            return;
        }
        singleByteXOR s = new singleByteXOR();

        if(args[0].equals("-t")) {
            //tests
            s.test();
            return;
        }

        if(args[0].equals("-d")) {
            //tests
            s.init("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
            return;
        }

        s.init(args[0]);
    }
}
