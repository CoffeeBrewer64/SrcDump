using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Office.Interop.Excel;
using System.IO;

namespace LanguageConvert
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                this.textBox1.Text = openFileDialog1.FileName;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (this.folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                this.textBox2.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void folderBrowserDialog1_HelpRequest(object sender, EventArgs e)
        {

        }

        private void proctag(ref string str)
        {
            string newstr;

            newstr = "\u0001\u0010YYYY";
            str = str.Replace("^YYYY", newstr);
            newstr = "\u0001\u0011MM";
            str = str.Replace("^MM", newstr);
            newstr = "\u0001\u0012DD";
            str = str.Replace("^DD", newstr);
            newstr = "\u0001\u0013HH:MN";
            str = str.Replace("^HH:^MN", newstr);

            newstr = "\u0001\u0014P";
            str = str.Replace("^player_no", newstr);
            str = str.Replace("^^PLAYERNO", newstr);

            newstr = "\u0002\u0010";
            str = str.Replace("^clb", newstr);
            newstr = "\u0002\u0011";
            str = str.Replace("^clr", newstr);

            newstr = "\u0003\u0010ABCD0123456789ABCDEFABCD0123456789ABCDEF";
            str = str.Replace("^^PLAYERNAME1", newstr);
            newstr = "\u0003\u0011ABCD0123456789ABCDEFABCD0123456789ABCDEF";
            str = str.Replace("^^PLAYERNAME2", newstr);
            newstr = "\u0003\u0012ABCD0123456789ABCDEFABCD0123456789ABCDEF";
            str = str.Replace("^^PLAYERNAME3", newstr);
            newstr = "\u0003\u0013ABCD0123456789ABCDEFABCD0123456789ABCDEF";
            str = str.Replace("^^PLAYERNAME4", newstr);

            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Microsoft.Office.Interop.Excel.Application app = new Microsoft.Office.Interop.Excel.Application();

            Microsoft.Office.Interop.Excel.Workbook workbook = app.Workbooks.Add(textBox1.Text);
            Microsoft.Office.Interop.Excel.Sheets sheets = workbook.Sheets;
         

            Microsoft.Office.Interop.Excel.Worksheet sheet = (Microsoft.Office.Interop.Excel.Worksheet)sheets.get_Item(1);

            Microsoft.Office.Interop.Excel.Range range;

            int i = 0, j = 0;
            string str = null;


            for(int k=2;k<10;k++)
            {
                for(i = 1;i<k-1;i++)
                {
                    j = k- i;
                    range = (Range)sheet.Cells[i, j];
                    str = range.Text.ToString();
                    if (str != null && str != "")
                        break;
                }
                if (str != null && str != "")
                    break;
            }

            if (str == null || str == "")
            {
                app.Quit();
                return;
            }


            int ox, oy;
            ox = i;
            oy = j;

            int ctx = 0, cty = 0;

            for (j = oy; ; j++)
            {
                range = (Range)sheet.Cells[ox, j];
                str = range.Text.ToString();
                if (str != null && str != "")
                    cty++;
                else
                    break;
            }
            for (i = ox; ; i++)
            {
                range = (Range)sheet.Cells[i, oy];
                str = range.Text.ToString();
                if (str != null && str != "")
                    ctx++;
                else
                    break;
            }

            string[,] strtable = new string[ctx, cty];
            string[,] strtabletext = new string[ctx, cty];

            for(i=ox;i<ox+ctx;i++)
            {
                for (j = oy; j < oy + cty; j++)
                {
                    range = (Range)sheet.Cells[i, j];
                    strtable[i - ox, j - oy] = range.Text.ToString();
                    strtabletext[i - ox, j - oy] = strtable[i - ox, j - oy];
                    strtable[i - ox, j - oy] = strtable[i - ox, j - oy].Trim();
                }
            }


            for (j = 0; j < cty; j++)
            {
                if (strtable[0,j] == "No")
                    continue;
                if (strtable[0,j] == "MSG_NAME")
                    continue;
                if (strtable[0,j] == "TargetPane")
                    continue;
                if (strtable[0, j] == "Remarks")
                    continue;
                if (strtable[0, j] == "NCL-Comment")
                    continue;
                if (strtable[0, j] == "NOA-Comment")
                    continue;
                if (strtable[0, j] == "NOE-Comment")
                    continue;
                if (strtable[0, j] == "ColorTag")
                    continue;
                if (strtable[0, j] == "redcolor")
                    continue;
                if (strtable[0, j] == "blackcolor")
                    continue;

                if ((strtable[0, j] == "Japanese") ||
                    (strtable[0, j] == "US-English") ||
                    (strtable[0, j] == "US-French") ||
                    (strtable[0, j] == "US-Spanish") ||
                    (strtable[0, j] == "US-Portuguese") ||
                    (strtable[0, j] == "EU-English") ||
                    (strtable[0, j] == "EU-French") ||
                    (strtable[0, j] == "EU-Spanish") ||
                    (strtable[0, j] == "EU-Portuguese") ||
                    (strtable[0, j] == "EU-German") ||
                    (strtable[0, j] == "EU-Italian") ||
                    (strtable[0, j] == "EU-Russian") ||
                    (strtable[0, j] == "EU-Dutch")
                    )
                {
                    StreamWriter sw = new StreamWriter(textBox2.Text + "\\" + strtable[0, j] + ".lang", false, Encoding.Unicode);
                    if (sw == null)
                        continue;
                    for (i = 1; i < ctx; i++)
                    {
                        proctag(ref strtabletext[i, j]);
                        sw.Write(strtabletext[i, j]);
                        sw.Write((char)0);
                    }
                    sw.Close();
                }
                else if ((strtable[0, j] == "JP-Scale") ||
                    (strtable[0, j] == "US-EN-Scale") ||
                    (strtable[0, j] == "US-FR-Scale") ||
                    (strtable[0, j] == "US-SP-Scale") ||
                    (strtable[0, j] == "US-PO-Scale") ||
                    (strtable[0, j] == "EU-EN-Scale") ||
                    (strtable[0, j] == "EU-FR-Scale") ||
                    (strtable[0, j] == "EU-SP-Scale") ||
                    (strtable[0, j] == "EU-PO-Scale") ||
                    (strtable[0, j] == "EU-GE-Scale") ||
                    (strtable[0, j] == "EU-IT-Scale") ||
                    (strtable[0, j] == "EU-RU-Scale") ||
                    (strtable[0, j] == "EU-DU-Scale")
                    )
                {
                    FileStream fs = new FileStream(textBox2.Text + "\\" + strtable[0, j] + ".scale", FileMode.Create);
                    if (fs == null)
                        continue;
                    BinaryWriter br = new BinaryWriter(fs);
                    for (i = 1; i < ctx; i++)
                    {
                        float ftemp = 1.0f;
                        strtable[i, j] = strtable[i, j].Trim();
                        if(strtable[i, j] != "")
                            ftemp = float.Parse(strtable[i, j]);
                        br.Write(ftemp);
                    }
                    br.Close();
                    fs.Close();
                }
            }
            app.Quit();
            MessageBox.Show("Done!");            
        }
    }
}
