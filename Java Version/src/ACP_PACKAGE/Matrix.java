package ACP_PACKAGE;

public class Matrix<T> {
    
    public int row = 0;
    public int col = 0;
    public double[][] values;
    
    public Matrix(int row, int col) {
        // TODO Auto-generated constructor stub
        this.row = row;
        this.col = col;
        this.values = new double[this.row][this.col];
        for (int i = 0; i < this.row; i++) {
            for (int j = 0; j < this.col; j++) {
                this.values[i][j] = 0;
            }
        }
    }

    public Matrix() {
        // TODO Auto-generated constructor stub
    }

    public static double Norm_Eclud(double[] vect) {
        double sum = 0;
        for (int i = 0; i < vect.length; i++) {
            sum += (vect[i] * vect[i]);
        }
        return Math.sqrt(sum);
    }

    public static double Norm_Inf(double[] vect) {
        double max = 0;
        for (int i = 0; i < vect.length - 1; i++) {
            if (Math.abs(vect[i + 1]) > Math.abs(vect[i])) {
                max = Math.abs(vect[i + 1]);
            }
        }
        return max;
    }

    public void GetMatrixTrans(Matrix m) {
        this.row = m.col;
        this.col = m.row;
        this.values = new double[this.row][this.col];
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.col; j++) {
                this.values[j][i] = m.values[i][j];
            }
        }
    }

    public void PrintMatrix() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                System.out.print(values[i][j] + "\t");
            }
            System.out.println();
        }
    }

    public void GetMatrixProd(Matrix X, Matrix Y) {
        try {
            if (X.col != Y.row) {
                throw new Exception();
            }
            double sum = 0;
            this.row = X.row;
            this.col = Y.col;
            this.values = new double[this.row][this.col];
            for (int i = 0; i < X.row; i++) {
                for (int j = 0; j < Y.col; j++) {
                    for (int k = 0; k < Y.row; k++) {
                        sum += X.values[i][k] * Y.values[k][j];
                    }
                    this.values[i][j] = sum;
                    sum = 0;
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static Matrix MCopy(Matrix m) {
        Matrix n = new Matrix(m.row, m.col);
        for (int i = 0; i < n.row; i++) {
            for (int j = 0; j < n.col; j++) {
                n.values[i][j] = m.values[i][j];
            }
        }
        return n;
    }

    public static Matrix GetM_Sous(Matrix x, Matrix y) {
        Matrix z = new Matrix(x.row, x.col);
        for (int i = 0; i < z.row; i++) {
            for (int j = 0; j < z.col; j++) {
                z.values[i][j] = x.values[i][j] - y.values[i][j];
            }
        }
        return z;
    }

}
