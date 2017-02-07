package RNA_PACKAGE;

import ACP_PACKAGE.ACP;
import ACP_PACKAGE.Matrix;

public class Viwer {

    public static void main(String[] args) {
        // TODO Auto-generated method stub
        System.out.println("\n---------\n  DATA  \n---------\n");
        Matrix data = new Matrix(4, 4);
        for (int i = 0; i < data.row; i++) {
            for (int j = 0; j < data.col; j++) {
                data.values[i][j] = i + j;
            }
        }
        data.PrintMatrix();

        System.out.println("\n---------\n  SOM   \n---------\n");
        SOM som = new SOM(data, 5);
        som.printMap();

        System.out.println("\n---------\nTRAINING\n---------\n");
        som.Train(0.001, 10000);
        som.printMap();

        System.out.println("\n---------\nClastring\n---------\n");
        som.Clastring();

        System.out.println("\n\n\n#################\nWith ACP Method\n#################\n");

        ACP acp = new ACP(data);
        Matrix ACPm = acp.GetACPMatrix();

        System.out.println("\n---------\nACP Matr\n---------\n");
        ACPm.PrintMatrix();

        System.out.println("\n---------\n  SOM   \n---------\n");
        SOM somACP = new SOM(ACPm, 5);
        som.printMap();

        System.out.println("\n---------\nTRAINING\n---------\n");
        somACP.Train(0.001, 10000);
        somACP.printMap();

        System.out.println("\n---------\nClastring\n---------\n");
        somACP.Clastring();
    }

}
