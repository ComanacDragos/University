import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.stream.Collectors;

public class Matrix {
    Integer[][] matrix;
    Integer lines, columns;
    String file;

    public Matrix(String file){
        this.file = file;
        readMatrix();
    }

    public Matrix(Integer lines, Integer columns, Boolean generateMatrix){
        this.file = "";
        this.lines = lines;
        this.columns = columns;
        matrix = new Integer[lines][columns];
        if(generateMatrix)
            generateMatrix();
    }

    public Matrix(Integer lines, Integer columns, String file){
        this.file = file;
        this.lines = lines;
        this.columns = columns;
        matrix = new Integer[lines][columns];
        generateMatrix();
        writeMatrix();
    }

    public Matrix(String file, Integer lines, Integer columns){
        this.file = file;
        this.lines = lines;
        this.columns = columns;
        matrix = new Integer[lines][columns];
        readMatrix();
    }


        public Integer get(MatrixEntry entry){
        return matrix[entry.line][entry.column];
    }

    public void set(MatrixEntry entry, Integer value){
        matrix[entry.line][entry.column] = value;
    }

    public Integer getLines() {
        return lines;
    }

    public Integer getColumns() {
        return columns;
    }

    void readMatrix(){
        try(BufferedReader reader = new BufferedReader(new FileReader(this.file))){
            String[] line = reader.readLine().split(",");
            lines = Integer.parseInt(line[0]);
            columns = Integer.parseInt(line[1]);
            matrix = new Integer[lines][columns];
            for(int i=0;i<lines;i++){
                line = reader.readLine().split(",");
                for(int j=0;j<columns;j++){
                   matrix[i][j] = Integer.parseInt(line[j]);
                }
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    void writeMatrix(){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter(file)))){
            writer.print(this);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    private void generateMatrix(){
        matrix = new Integer[lines][columns];
        Random rand = new Random();
        for(int i=0;i<lines;i++){
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = rand.nextInt()%100;
            }
        }
    }

    @Override
    public String toString() {
        String matrixRepresentation =
                Arrays.stream(matrix).map(line ->{
                    return Arrays.stream(line)
                            .map(Object::toString)
                            .collect(Collectors.joining(","));
        }).collect(Collectors.joining("\n"));

        return lines + "," + columns + "\n" + matrixRepresentation;
    }
}
