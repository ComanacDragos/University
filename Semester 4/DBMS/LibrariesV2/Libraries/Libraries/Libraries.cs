using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Libraries.Service;
using Libraries.Domain;
using Libraries.Exceptions;

namespace Libraries
{
    public partial class Libraries : Form
    {
        public OneToManyService<int, Title, int, Character> MyService { get; set; }

        public Libraries()
        {
            InitializeComponent();
        }

        private void Libraries_Load(object sender, EventArgs e)
        {
            titlesTable.DataSource = MyService.getParentDataSource();
            titlesTable.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            titlesTable.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;

            charactersTable.DataSource = MyService.getChildDataSource();
            charactersTable.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            charactersTable.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            charactersTable.Columns[2].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            charactersTable.Columns[3].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;

            charactersTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            titlesTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            roleComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
           
            foreach(Character.Role role in Enum.GetValues(typeof(Character.Role)))
                roleComboBox.Items.Add(role);            
        }

        private void addCharacterButton_Click(object sender, EventArgs e)
        {
            try
            {
                MyService.Add(new Character(Int32.Parse(characterIdTextBox.Text),
                                            Int32.Parse(titleIdTextBox.Text),
                                            fullNameTextBox.Text,
                                            Character.StringToRole(roleComboBox.Text)
                                            )
                              );
            }
            catch (MyException exc)
            {
                MessageBox.Show(exc.Message, "Could not add character");
            }
            catch (FormatException)
            {
                MessageBox.Show("Both TitleId and CharacterId must be integers", "Error");
            }
        }
        private void deleteCharacterButton_Click(object sender, EventArgs e)
        {
            try
            {
                MyService.Remove(Int32.Parse(characterIdTextBox.Text));
            }
            catch (MyException exc)
            {
                MessageBox.Show(exc.Message, "Could not delete character");
            }
            catch (FormatException)
            {
                MessageBox.Show("Both TitleId and CharacterId must be integers", "Error");
            }
        }

        private void updateCharacterButton_Click(object sender, EventArgs e)
        {
            try
            {
                MyService.Update(new Character(Int32.Parse(characterIdTextBox.Text),
                                            Int32.Parse(titleIdTextBox.Text),
                                            fullNameTextBox.Text,
                                            Character.StringToRole(roleComboBox.Text)
                                            )
                              );
            }
            catch (MyException exc)
            {
                MessageBox.Show(exc.Message, "Could not update character");
            }
            catch (FormatException)
            {
                MessageBox.Show("Both TitleId and CharacterId must be integers", "Error");
            }
        }

        private void charactersTable_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (charactersTable.SelectedRows.Count == 1)
            {
                DataGridViewRow dataRow = charactersTable.SelectedRows[0];
                characterIdTextBox.Text = dataRow.Cells[0].Value.ToString();
                titleIdTextBox.Text = dataRow.Cells[1].Value.ToString();
                fullNameTextBox.Text = dataRow.Cells[2].Value.ToString();
                roleComboBox.Text = dataRow.Cells[3].Value.ToString();
            }
        }

        private void titlesTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (titlesTable.SelectedRows.Count == 1)
            {
                DataGridViewRow dataRow = titlesTable.SelectedRows[0];
                titleIdTextBox.Text = dataRow.Cells[0].Value.ToString();

                charactersTable_CellContentClick(null, null);
            }
        }

        private void updateDBButton_Click(object sender, EventArgs e)
        {
            try
            {
                MyService.updateChild();

                MessageBox.Show("DB updated", "Success");
            }
            catch (MyException exc)
            {
                MessageBox.Show(exc.Message, "Could not update table");
            }
        }
    }
}
