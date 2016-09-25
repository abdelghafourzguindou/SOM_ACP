package RNA_PACKAGE;

import ACP_PACKAGE.Matrix;

public class SOM {

    public SOM() {
        // TODO Auto-generated constructor stub
    }

    public SOM(Matrix data, int GSize) {
        // TODO Auto-generated constructor stub
        GridDim = GSize;
        GridSize = GSize / 2;
        WeightSize = data.col;
        InputSize = data.row;
        TrainData = data;
        Map = new Node[GridDim][GridDim];
        for (int i = 0; i < GridDim; i++) {
            for (int j = 0; j < GridDim; j++) {
                Map[i][j] = new Node(i, j, WeightSize);
            }
        }
    }

    private static int GridSize;
    private static int GridDim;
    private static double StartLearningRate;
    private static int MaxIteration;
    private static int WeightSize;
    private static int InputSize;
    private static Matrix TrainData;

    public static Node Winner;
    public static Node[][] Map;

    public double ReduceLearninRate(int iteration) {
        return StartLearningRate * Math.exp(-((double) (iteration) / MaxIteration));
    }

    public double DetrRadius(int iteration) {
        return GridSize * Math.exp(-((double) (iteration * Math.log(GridSize)) / MaxIteration));
    }

    public double GetInfluence(double dis, double radius) {
        return Math.exp(-(double) dis / (2 * Math.pow(radius, 2)));
    }

    public double getNeighboursDis(int i, int j) {
        return Math.pow((Winner.x - Map[i][j].x), 2)
                + Math.pow((Winner.y - Map[i][j].y), 2);
    }

    public static void GetWinner(double[] x) {
        double LowestDistance = 999999;
        double dist = 0;
        for (int i = 0; i < GridDim; i++) {
            for (int j = 0; j < GridDim; j++) {
                dist = Map[i][j].getEcluDistWeight(x);
                if (dist < LowestDistance) {
                    LowestDistance = dist;
                    Winner = Map[i][j];
                }
            }
        }
    }

    public void Train(double sLR, int MaxItr) {

        StartLearningRate = sLR;
        MaxIteration = MaxItr;

        int itr = 0;
        double error = 0;
        double Merror = 999999;
        double NeighbourhoodRadius = 0;
        double LearningRate = 0;
        double dist = 0;
        double Influence = 0;

        double[] THISvect = new double[WeightSize];

        do {

            for (int thisVect = 0; thisVect < InputSize; thisVect++) {
                for (int j = 0; j < WeightSize; j++) {
                    THISvect[j] = TrainData.values[thisVect][j];
                }
                GetWinner(THISvect);
                error += Winner.getEcluDistWeight(THISvect);
                NeighbourhoodRadius = DetrRadius(itr);
                LearningRate = ReduceLearninRate(itr);
                for (int i = 0; i < GridDim; i++) {
                    for (int j = 0; j < GridDim; j++) {
                        dist = getNeighboursDis(i, j);
                        if (dist < (NeighbourhoodRadius * NeighbourhoodRadius)) {
                            Influence = GetInfluence(dist, NeighbourhoodRadius);
                            Map[i][j].AdjustWeights(THISvect,
                                    LearningRate,
                                    Influence);
                        }
                    }
                }
            }
            itr++;
            Merror = error / InputSize;
            error = 0;
        } while (Merror > LearningRate && itr < MaxIteration);
    }

    public void printMap() {
        for (int i = 0; i < GridDim; i++) {
            for (int j = 0; j < GridDim; j++) {
                Map[i][j].PrintWeight();
                System.out.print("\t");
                //System.out.print(Map[i][j].x + "-" + Map[i][j].y+"\t");
            }
            System.out.println();
        }
    }

    public void Clastring() {
        double[] thisVect = new double[WeightSize];
        for (int vct = 0; vct < InputSize; vct++) {
            for (int i = 0; i < WeightSize; i++) {
                thisVect[i] = TrainData.values[vct][i];
            }
            GetWinner(thisVect);
            Winner.PrintWeight();
        }
    }
}
