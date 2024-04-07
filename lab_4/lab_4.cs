using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
 
namespace potoki
 
{
    public partial class Form1 : Form
    {
 
        public Form1()
        {
            InitializeComponent();
            
        }
 
        int count;
        static Mutex mutexObj = new Mutex();
       
 
        private void READ() {
            mutexObj.WaitOne();
 
            textBox2.Text += Thread.CurrentThread.Name + " содержит: " + count + " слов\r\n";
            // textBox1.Text = null; // пробовал делать через if (textBox1.Text == null) чтобы проверить, есть ли что то в писателе, что можно почитать, но не получилась. 
            Thread.Sleep(1000);// просто задерживает поток чтоб понять какой якобы работает 
            mutexObj.ReleaseMutex();
 
        }
 
        private void WRITE()
        {
            mutexObj.WaitOne();
            
                string[] a1 = new string[10] { "Товарищ!", "С другой стороны ", "Равным образом ", "Не следует, однако, забыть, что ", "Таким образом ", "Повседневная практика показыват, что ", "Значимость этих проблем настолько очевидная, что ", "Разнообразный и богатый опыт ", "Задача организации, в особенности же ", "Идейные соображения высокого порядка, а также " };
                string[] a2 = new string[10] { "реализация намеченных плановых заданий ", "рамки и место обучения кадров ", "постоянный количественный рост и сфера нашей активности ", "сложившаеся структура организации ", "новая модель организационной деятельности ", "дальнейшее развитие различных форм деятельности ", "постоянное информационно-пропагандисткое обеспечение нашей деятельности ", "управление и развитие структуры ", "консультация с широким активом ", "начало повседневной работы по формированию позиции" };
                string[] a3 = new string[10] { "играет важную роль в формировании ", "требует от наз анализа ", "требует определения и уточнения ", "способствует подготовке и реализации ", "обеспечивает широкому кругу ", "участие в формировании ", "в значительной степени обуславливает создание ", "позволяет оценить значение, представляет собой интересный эксперимент ", "позволяет выполнять разные задачи ", "проверки влечет за собой интересный процесс внедрения и модернизации" };
                string[] a4 = new string[10] { "существующим финансовых и административных условий.", "дальнейших направлений развития.", "системы массового участия.", "позиций, занимаемых участниками в отношении поставленных задач.", "новых предложений.", "направлений прогрессивного развития.", "системы обучения кадров, соответствующей насущным потребностям.", "соответствующих условий активизации.", "модели развития.", "форм воздействия." };
                Random rand = new Random();
// это все генератор слов
                textBox1.Text += Thread.CurrentThread.Name + (a1[rand.Next(a1.Length)]) + (a2[rand.Next(a2.Length)]) + (a3[rand.Next(a3.Length)]) + (a4[rand.Next(a4.Length)]);
// из-за Thread.CurrentThread.Name  слова считаются не правильно, но не суть, это пока для удобства отслеживания номера потока
 
 
                string s = textBox1.Text.ToString();
 
                count = s.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries).Length;// Считает слова типа...
                Thread.Sleep(1000);// просто задерживает поток чтоб понять какой якобы работает 
               
            
            mutexObj.ReleaseMutex();
 
        }
 
 
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
 
        }
 
        private void textBox2_TextChanged(object sender, EventArgs e)
        {
          
        }
        
        private void button1_Click(object sender, EventArgs e)
        {
            CheckForIllegalCrossThreadCalls = false;
 
            for (int i = 0; i < 9; i++)
            {
               
                    Thread w = new Thread(WRITE);
                    w.Start();
                    w.Name = "Поток " + i.ToString();//из-за этого считает слова  не правильно, сделано для номера потока.
              
                    Thread r = new Thread(READ);
                    r.Start();
                    r.Name = "Поток " + i.ToString();
                }
            }
            
        }
 
    }