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
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.parentGridVIew = new System.Windows.Forms.DataGridView();
            this.childGridView = new System.Windows.Forms.DataGridView();
            this.childLabel = new System.Windows.Forms.Label();
            this.parentLabel = new System.Windows.Forms.Label();
            this.updateChildButton = new System.Windows.Forms.Button();
            this.updateParentButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.parentGridVIew)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.childGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // parentGridVIew
            // 
            this.parentGridVIew.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentGridVIew.Location = new System.Drawing.Point(12, 29);
            this.parentGridVIew.Name = "parentGridVIew";
            this.parentGridVIew.Size = new System.Drawing.Size(461, 346);
            this.parentGridVIew.TabIndex = 18;
            // 
            // childGridView
            // 
            this.childGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childGridView.Location = new System.Drawing.Point(479, 29);
            this.childGridView.Name = "childGridView";
            this.childGridView.Size = new System.Drawing.Size(472, 346);
            this.childGridView.TabIndex = 19;
            // 
            // childLabel
            // 
            this.childLabel.AutoSize = true;
            this.childLabel.Location = new System.Drawing.Point(727, 9);
            this.childLabel.Name = "childLabel";
            this.childLabel.Size = new System.Drawing.Size(30, 13);
            this.childLabel.TabIndex = 20;
            this.childLabel.Text = "Child";
            this.childLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // parentLabel
            // 
            this.parentLabel.AutoSize = true;
            this.parentLabel.Location = new System.Drawing.Point(232, 9);
            this.parentLabel.Name = "parentLabel";
            this.parentLabel.Size = new System.Drawing.Size(38, 13);
            this.parentLabel.TabIndex = 21;
            this.parentLabel.Text = "Parent";
            // 
            // updateChildButton
            // 
            this.updateChildButton.Location = new System.Drawing.Point(652, 381);
            this.updateChildButton.Name = "updateChildButton";
            this.updateChildButton.Size = new System.Drawing.Size(200, 23);
            this.updateChildButton.TabIndex = 22;
            this.updateChildButton.Text = "Child";
            this.updateChildButton.UseVisualStyleBackColor = true;
            this.updateChildButton.Click += new System.EventHandler(this.updateChildButton_Click);
            // 
            // updateParentButton
            // 
            this.updateParentButton.Location = new System.Drawing.Point(169, 381);
            this.updateParentButton.Name = "updateParentButton";
            this.updateParentButton.Size = new System.Drawing.Size(200, 23);
            this.updateParentButton.TabIndex = 23;
            this.updateParentButton.Text = "Parent";
            this.updateParentButton.UseVisualStyleBackColor = true;
            this.updateParentButton.Click += new System.EventHandler(this.updateParentButton_Click);
            // 
            // Libraries
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(977, 410);
            this.Controls.Add(this.updateParentButton);
            this.Controls.Add(this.updateChildButton);
            this.Controls.Add(this.parentLabel);
            this.Controls.Add(this.childLabel);
            this.Controls.Add(this.childGridView);
            this.Controls.Add(this.parentGridVIew);
            this.Name = "Libraries";
            this.Text = "Libraries";
            this.Load += new System.EventHandler(this.Libraries_Load);
            ((System.ComponentModel.ISupportInitialize)(this.parentGridVIew)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.childGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.DataGridView parentGridVIew;
        private System.Windows.Forms.DataGridView childGridView;
        private System.Windows.Forms.Label childLabel;
        private System.Windows.Forms.Label parentLabel;
        private System.Windows.Forms.Button updateChildButton;
        private System.Windows.Forms.Button updateParentButton;
    }
}

