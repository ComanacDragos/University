import java.awt.*;

import javax.swing.*;

public class GridGUI extends JFrame {

    private final JPanel[][] gridPanels; // Panels representing each grid space in the environment
    int rows, cols;

    public GridGUI(int rows, int cols) {
        super("Grid Environment");
        this.rows = rows;
        this.cols = cols;
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Create the grid panels and add them to the GUI
        gridPanels = new JPanel[rows][cols];
        JPanel mainPanel = new JPanel(new GridLayout(rows, cols));
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                JPanel gridPanel = new JPanel();
                gridPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
                gridPanels[r][c] = gridPanel;
                mainPanel.add(gridPanel);
            }
        }
        setContentPane(mainPanel);

        pack();
        setSize(700, 700);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public void updateGrid(Cell[][] grid) {
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++){
                JPanel panel = gridPanels[i][j];
                panel.setBackground(null);
                panel.removeAll();

                Cell cell = grid[i][j];

                if(cell.agentId > -1){
                    panel.setBackground(Color.GREEN);
                    String text = String.valueOf(cell.agentId);
                    if(cell.isDirty){
                        text += " cleaning";
                    }
                    JLabel jlabel = new JLabel(text, SwingConstants.CENTER);
                    if(cell.isDirty)
                        jlabel.setForeground(Color.RED);
                    jlabel.setPreferredSize(new Dimension(70, 50));
                    panel.add(jlabel);

                    panel.revalidate();
                    panel.repaint();
                }else{
                    if(cell.isDirty)
                        panel.setBackground(Color.BLACK);
                    else if(cell.visited)
                        panel.setBackground(Color.BLUE);
                }
            }
    }

}
