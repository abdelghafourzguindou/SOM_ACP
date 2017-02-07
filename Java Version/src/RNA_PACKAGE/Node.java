package RNA_PACKAGE;

public class Node {

    public Node(int x, int y, int size) {
        // TODO Auto-generated constructor stub
        this.x = x;
        this.y = y;
        Weight = new double[size];
        for (int i = 0; i < size; i++) {
            Weight[i] = Math.random();
        }
    }

    public Node() {

    }

    public int x;
    public int y;
    public double[] Weight;

    public double getEcluDistWeight(double[] x) {
        double norm = 0;
        for (int i = 0; i < Weight.length; i++) {
            norm += ((x[i] - Weight[i]) * (x[i] - Weight[i]));
        }
        return Math.sqrt(norm);
    }

    public void AdjustWeights(double[] t,
            double LearningRate,
            double Influence) {
        for (int i = 0; i < Weight.length; i++) {
            Weight[i] += (LearningRate * Influence) * (t[i] - Weight[i]);
        }
    }

    public void PrintWeight() {
        System.out.print("(\t");
        for (int i = 0; i < Weight.length; i++) {
            System.out.print(Weight[i] + "\t");
        }
        System.out.print(")");
    }

}
