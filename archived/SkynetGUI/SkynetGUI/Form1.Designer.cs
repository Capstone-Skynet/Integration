namespace SkynetGUI
{
    partial class Form1
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
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.status_time_label = new System.Windows.Forms.ToolStripStatusLabel();
            this.status_label = new System.Windows.Forms.ToolStripStatusLabel();
            this.main_image_box = new System.Windows.Forms.PictureBox();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button_test = new System.Windows.Forms.Button();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.main_image_box)).BeginInit();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.status_time_label,
            this.status_label});
            this.statusStrip1.Location = new System.Drawing.Point(0, 426);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(800, 24);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "status";
            // 
            // status_time_label
            // 
            this.status_time_label.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Right;
            this.status_time_label.Name = "status_time_label";
            this.status_time_label.Size = new System.Drawing.Size(43, 19);
            this.status_time_label.Text = "Time: ";
            // 
            // status_label
            // 
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(742, 19);
            this.status_label.Spring = true;
            this.status_label.Text = "status";
            this.status_label.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // main_image_box
            // 
            this.main_image_box.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.main_image_box.Location = new System.Drawing.Point(12, 12);
            this.main_image_box.Name = "main_image_box";
            this.main_image_box.Size = new System.Drawing.Size(399, 251);
            this.main_image_box.TabIndex = 1;
            this.main_image_box.TabStop = false;
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(448, 150);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(340, 199);
            this.listBox1.TabIndex = 3;
            // 
            // button_test
            // 
            this.button_test.Location = new System.Drawing.Point(486, 47);
            this.button_test.Name = "button_test";
            this.button_test.Size = new System.Drawing.Size(75, 23);
            this.button_test.TabIndex = 4;
            this.button_test.Text = "button1";
            this.button_test.UseVisualStyleBackColor = true;
            this.button_test.Click += new System.EventHandler(this.button_test_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button_test);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.main_image_box);
            this.Controls.Add(this.statusStrip1);
            this.Name = "Form1";
            this.Text = "SkynetGUI";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.main_image_box)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel status_time_label;
        private System.Windows.Forms.ToolStripStatusLabel status_label;
        private System.Windows.Forms.PictureBox main_image_box;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button_test;
    }
}

