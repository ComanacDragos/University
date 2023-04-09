import java.awt.*;

import javax.swing.*;

public class GridGUI extends JFrame {

    private JPanel[][] gridPanels; // Panels representing each grid space in the environment

    public GridGUI(int rows, int cols) {
        super("Grid Environment");

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

    public void updateGrid(int x, int y, int id) {
        for (JPanel[] gridPanel : gridPanels) {
            for (JPanel jPanel : gridPanel) {
                if (jPanel.getBackground() == Color.RED) {
                    jPanel.setBackground(null);

                }
                jPanel.removeAll();
            }
        }
        JPanel panel = gridPanels[y][x];

        panel.setBackground(Color.RED);
        JLabel jlabel = new JLabel(String.valueOf(id), SwingConstants.CENTER);
        jlabel.setBackground(Color.WHITE);
        jlabel.setPreferredSize(new Dimension(50, 50));
        panel.add(jlabel);

        panel.revalidate();
        panel.repaint();
    }

}
