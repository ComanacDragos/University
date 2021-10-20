public class MatrixRepo {
    Matrix a, b, c;

    MatrixRepo(Matrix a, Matrix b){
        this.a = a;
        this.b = b;
        if(!a.getColumns().equals(b.getLines()))
            throw new RuntimeException("Matrices are incompatible");
        c = new Matrix(a.getLines(), b.getColumns(), false);
    }

    public void computeElement(MatrixEntry entry){
        c.set(entry, 0);
        for(int i=0;i<a.getColumns();i++){
            c.set(entry, c.get(entry)
                    + a.get(new MatrixEntry(entry.getLine(), i))
                    * b.get(new MatrixEntry(i, entry.getColumn()))
            );
        }
    }

    public Matrix getResults() {
        return c;
    }
}
