namespace Libraries
{
    partial class Libraries
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.titlesTable = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.characterIdTextBox = new System.Windows.Forms.TextBox();
            this.titleIdTextBox = new System.Windows.Forms.TextBox();
            this.fullNameTextBox = new System.Windows.Forms.TextBox();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.addCharacterButton = new System.Windows.Forms.Button();
            this.charactersTable = new System.Windows.Forms.DataGridView();
            this.Characters = new System.Windows.Forms.Label();
            this.deleteCharacterButton = new System.Windows.Forms.Button();
            this.updateCharacterButton = new System.Windows.Forms.Button();
            this.roleComboBox = new System.Windows.Forms.ComboBox();
            this.updateDBButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.titlesTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.charactersTable)).BeginInit();
            this.SuspendLayout();
            // 
            // titlesTable
            // 
            this.titlesTable.AccessibleName = "titlesTable";
            this.titlesTable.AllowUserToAddRows = false;
            this.titlesTable.AllowUserToDeleteRows = false;
            this.titlesTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.titlesTable.Location = new System.Drawing.Point(12, 31);
            this.titlesTable.Name = "titlesTable";
            this.titlesTable.ReadOnly = true;
            this.titlesTable.Size = new System.Drawing.Size(338, 234);
            this.titlesTable.TabIndex = 0;
            this.titlesTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.titlesTable_CellClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(158, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(32, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Titles";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(438, 298);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "CharacterId";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(464, 332);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "TitleId";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(448, 367);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Full name";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(471, 398);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Role";
            // 
            // characterIdTextBox
            // 
            this.characterIdTextBox.Location = new System.Drawing.Point(506, 295);
            this.characterIdTextBox.Name = "characterIdTextBox";
            this.characterIdTextBox.Size = new System.Drawing.Size(100, 20);
            this.characterIdTextBox.TabIndex = 6;
            // 
            // titleIdTextBox
            // 
            this.titleIdTextBox.Location = new System.Drawing.Point(506, 329);
            this.titleIdTextBox.Name = "titleIdTextBox";
            this.titleIdTextBox.Size = new System.Drawing.Size(100, 20);
            this.titleIdTextBox.TabIndex = 7;
            // 
            // fullNameTextBox
            // 
            this.fullNameTextBox.Location = new System.Drawing.Point(506, 364);
            this.fullNameTextBox.Name = "fullNameTextBox";
            this.fullNameTextBox.Size = new System.Drawing.Size(100, 20);
            this.fullNameTextBox.TabIndex = 8;
            // 
            // addCharacterButton
            // 
            this.addCharacterButton.Location = new System.Drawing.Point(115, 283);
            this.addCharacterButton.Name = "addCharacterButton";
            this.addCharacterButton.Size = new System.Drawing.Size(119, 23);
            this.addCharacterButton.TabIndex = 10;
            this.addCharacterButton.Text = "Add character";
            this.addCharacterButton.UseVisualStyleBackColor = true;
            this.addCharacterButton.Click += new System.EventHandler(this.addCharacterButton_Click);
            // 
            // charactersTable
            // 
            this.charactersTable.AllowUserToAddRows = false;
            this.charactersTable.AllowUserToDeleteRows = false;
            this.charactersTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.charactersTable.Location = new System.Drawing.Point(356, 31);
            this.charactersTable.Name = "charactersTable";
            this.charactersTable.ReadOnly = true;
            this.charactersTable.Size = new System.Drawing.Size(393, 234);
            this.charactersTable.TabIndex = 11;
            this.charactersTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.charactersTable_CellContentClick);
            // 
            // Characters
            // 
            this.Characters.AutoSize = true;
            this.Characters.Location = new System.Drawing.Point(531, 9);
            this.Characters.Name = "Characters";
            this.Characters.Size = new System.Drawing.Size(58, 13);
            this.Characters.TabIndex = 12;
            this.Characters.Text = "Characters";
            // 
            // deleteCharacterButton
            // 
            this.deleteCharacterButton.Location = new System.Drawing.Point(115, 317);
            this.deleteCharacterButton.Name = "deleteCharacterButton";
            this.deleteCharacterButton.Size = new System.Drawing.Size(119, 23);
            this.deleteCharacterButton.TabIndex = 13;
            this.deleteCharacterButton.Text = "Delete character";
            this.deleteCharacterButton.UseVisualStyleBackColor = true;
            this.deleteCharacterButton.Click += new System.EventHandler(this.deleteCharacterButton_Click);
            // 
            // updateCharacterButton
            // 
            this.updateCharacterButton.Location = new System.Drawing.Point(115, 347);
            this.updateCharacterButton.Name = "updateCharacterButton";
            this.updateCharacterButton.Size = new System.Drawing.Size(119, 23);
            this.updateCharacterButton.TabIndex = 14;
            this.updateCharacterButton.Text = "Update character";
            this.updateCharacterButton.UseVisualStyleBackColor = true;
            this.updateCharacterButton.Click += new System.EventHandler(this.updateCharacterButton_Click);
            // 
            // roleComboBox
            // 
            this.roleComboBox.FormattingEnabled = true;
            this.roleComboBox.Location = new System.Drawing.Point(506, 393);
            this.roleComboBox.Name = "roleComboBox";
            this.roleComboBox.Size = new System.Drawing.Size(100, 21);
            this.roleComboBox.TabIndex = 16;
            // 
            // updateDBButton
            // 
            this.updateDBButton.Location = new System.Drawing.Point(115, 376);
            this.updateDBButton.Name = "updateDBButton";
            this.updateDBButton.Size = new System.Drawing.Size(119, 23);
            this.updateDBButton.TabIndex = 17;
            this.updateDBButton.Text = "Update DB";
            this.updateDBButton.UseVisualStyleBackColor = true;
            this.updateDBButton.Click += new System.EventHandler(this.updateDBButton_Click);
            // 
            // Libraries
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(761, 450);
            this.Controls.Add(this.updateDBButton);
            this.Controls.Add(this.roleComboBox);
            this.Controls.Add(this.updateCharacterButton);
            this.Controls.Add(this.deleteCharacterButton);
            this.Controls.Add(this.Characters);
            this.Controls.Add(this.charactersTable);
            this.Controls.Add(this.addCharacterButton);
            this.Controls.Add(this.fullNameTextBox);
            this.Controls.Add(this.titleIdTextBox);
            this.Controls.Add(this.characterIdTextBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.titlesTable);
            this.Name = "Libraries";
            this.Text = "Libraries";
            this.Load += new System.EventHandler(this.Libraries_Load);
            ((System.ComponentModel.ISupportInitialize)(this.titlesTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.charactersTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView titlesTable;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox characterIdTextBox;
        private System.Windows.Forms.TextBox titleIdTextBox;
        private System.Windows.Forms.TextBox fullNameTextBox;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Button addCharacterButton;
        private System.Windows.Forms.DataGridView charactersTable;
        private System.Windows.Forms.Label Characters;
        private System.Windows.Forms.Button deleteCharacterButton;
        private System.Windows.Forms.Button updateCharacterButton;
        private System.Windows.Forms.ComboBox roleComboBox;
        private System.Windows.Forms.Button updateDBButton;
    }
}

