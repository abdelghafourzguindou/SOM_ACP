package ACP_PACKAGE;

import java.util.LinkedList;

public class ACP extends Matrix {

    public ACP(Matrix data) {
        // TODO Auto-generated constructor stub
        ACP.data = data;
    }

    private static Matrix data;

    private static double[] GetAVGvect() {
        double[] g = new double[data.col];
        int k = 0;
        double sum = 0;
        for (int i = 0; i < data.col; i++) {
            for (int j = 0; j < data.row; j++) {
                sum += data.values[j][i];
            }
            g[k] = sum / data.row;
            k++;
            sum = 0;
        }
        return g;
    }

    private static Matrix GetCenterMatrix() {
        double[] g = GetAVGvect();
        Matrix Y = new Matrix(data.row, data.col);
        for (int i = 0; i < Y.row; i++) {
            for (int j = 0; j < Y.col; j++) {
                Y.values[i][j] = data.values[i][j] - g[j];
            }
        }
        return Y;
    }

    private static Matrix GetVarMatrix() {
        Matrix Y = GetCenterMatrix();
        Matrix T = new Matrix();
        T.GetMatrixTrans(Y);
        Matrix A = new Matrix();
        A.GetMatrixProd(T, Y);
        Matrix V = new Matrix(A.row, A.col);
        for (int i = 0; i < V.row; i++) {
            for (int j = 0; j < V.row; j++) {
                V.values[i][j] = A.values[i][j] / data.row;
            }
        }
        return V;
    }

    private static Matrix GetMDIVar() {
        Matrix V = GetVarMatrix();
        Matrix D1_S2 = new Matrix(V.row, V.col);
        for (int i = 0; i < V.row; i++) {
            for (int j = 0; j < V.col; j++) {
                if (i == j) {
                    D1_S2.values[i][i] = (1 / V.values[i][i]);
                }
            }
        }
        return D1_S2;
    }

    private static Matrix GetMDIET() {
        Matrix d = GetMDIVar();
        Matrix D1_S = new Matrix(d.row, d.col);
        for (int i = 0; i < D1_S.row; i++) {
            for (int j = 0; j < D1_S.col; j++) {
                if (i == j) {
                    D1_S.values[i][i] = Math.sqrt(d.values[i][i]);
                }
            }
        }
        return D1_S;
    }

    private static Matrix GetMCR() {
        Matrix Y = GetCenterMatrix();
        Matrix D1_S = GetMDIET();
        Matrix Z = new Matrix();
        Z.GetMatrixProd(Y, D1_S);
        return Z;
    }

    private static Matrix GetMCoor() {
        Matrix V = GetVarMatrix();
        Matrix D = GetMDIET();
        Matrix A = new Matrix();
        A.GetMatrixProd(D, V);
        Matrix R = new Matrix();
        R.GetMatrixProd(A, D);
        return R;
    }

    public final Matrix GetACPMatrix() {

        Matrix R = GetMCoor();
        int DIM = R.row;
        double MaxVP = 0;

        Matrix x = new Matrix(1, DIM);
        Matrix y0 = new Matrix(1, DIM);
        Matrix y = new Matrix(1, DIM);
        Matrix Y_Y0 = new Matrix(1, DIM);
        Matrix A = new Matrix(1, DIM);

        LinkedList<Double> PValuelist = new LinkedList<Double>();
        Matrix PVect = new Matrix(DIM, DIM);

        for (int i = 0; i < DIM; i++) {

            for (int i1 = 0; i1 < DIM; i1++) {
                x.values[0][i1] = i1 == 0 ? 1 : 0;
            }

            for (int i1 = 0; i1 < DIM; i1++) {
                y0.values[0][i1] = x.values[0][i1] / Norm_Eclud(x.values[0]);
            }

            do {
                y = MCopy(y0);

                for (int i1 = 0; i1 < DIM; i1++) {
                    for (int j = 0; j < DIM; j++) {
                        x.values[0][i1] += R.values[i1][j] * y0.values[0][j];
                    }
                }

                for (int i2 = 0; i2 < DIM; i2++) {
                    y0.values[0][i2] = x.values[0][i2] / Norm_Eclud(x.values[0]);
                }

                Y_Y0 = GetM_Sous(y, y0);

            } while (Norm_Inf(Y_Y0.values[0]) > 0.00001
                    && Norm_Eclud(Y_Y0.values[0]) < (Norm_Eclud(y.values[0])
                    + Norm_Eclud(y0.values[0])));

            //Get the value of MaxVP (Propre value)
            MaxVP = 0;
            A.GetMatrixProd(y0, R);
            for (int i1 = 0; i1 < DIM; i1++) {
                MaxVP += A.values[0][i1] * y0.values[0][i1];
            }

            PValuelist.add(MaxVP);

            for (int d = 0; d < DIM; d++) {
                PVect.values[i][d] = y0.values[0][d];
            }

            //Get the new R matrix
            for (int g = 0; g < DIM; g++) {
                for (int l = 0; l < DIM; l++) {
                    R.values[g][l] = R.values[g][l] - (MaxVP * y0.values[0][g] * y0.values[0][l]);
                }
            }
        }

        double sum1 = 0;
        double sum2 = 0;
        int SIZE = 0;

        Matrix impPvect = null;

        for (int i = 0; i < DIM; i++) {
            sum1 += PValuelist.get(i);
        }
        for (int i = 0; i < DIM; i++) {
            sum2 += PValuelist.get(i);
            SIZE++;
            if (sum2 / sum1 >= 0.8) {
                impPvect = new Matrix(SIZE, DIM);
                for (int j = 0; j < SIZE; j++) {
                    for (int k = 0; k < DIM; k++) {
                        impPvect.values[j][k] = PVect.values[j][k];
                    }
                }
                break;
            }
        }

        Matrix Z = GetMCR();
        Matrix F = new Matrix();
        F.GetMatrixTrans(impPvect);
        Matrix C = new Matrix();
        C.GetMatrixProd(Z, F);

        return C;
    }

}
