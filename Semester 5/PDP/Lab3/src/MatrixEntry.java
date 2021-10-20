public class MatrixEntry {
    Integer line, column;
    MatrixEntry(Integer line, Integer column){
        this.line = line;
        this.column = column;
    }

    public Integer getLine() {
        return line;
    }

    public Integer getColumn() {
        return column;
    }

    @Override
    public String toString() {
        return "(" + line + ", " + column + ")";
    }
}

