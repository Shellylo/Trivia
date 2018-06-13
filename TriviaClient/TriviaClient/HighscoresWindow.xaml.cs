using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for HighscoresWindow.xaml
    /// </summary>
    public partial class HighscoresWindow : Window
    {
        private Client client;

        public HighscoresWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
            ShowHighscores();
        }

        public void ShowHighscores()
        {
            try
            {
                JsonResponsePacketDeserializer.HighscoreResponse scoresResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.HighscoreResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.GETHIGHSCORES_REQ_CODE);
                if (scoresResp.status == 1)
                {
                    List<JsonResponsePacketDeserializer.Highscore> scoresList = scoresResp.highscores;
                    for (int i = 0; i < scoresList.Count; i++)
                    {
                        JsonResponsePacketDeserializer.Highscore highscore = scoresList[i];
                        switch (i)
                        {
                            case 0:
                                username1.Text = highscore.username;
                                gscore1.Text = (highscore.score).ToString();
                                gdate1.Text = highscore.time;
                                break;
                            case 1:
                                username2.Text = highscore.username;
                                gscore2.Text = (highscore.score).ToString();
                                gdate2.Text = highscore.time;
                                break;
                            case 2:
                                username3.Text = highscore.username;
                                gscore3.Text = (highscore.score).ToString();
                                gdate3.Text = highscore.time;
                                break;
                            case 3:
                                username4.Text = highscore.username;
                                gscore4.Text = (highscore.score).ToString();
                                gdate4.Text = highscore.time;
                                break;
                            case 4:
                                username5.Text = highscore.username;
                                gscore5.Text = (highscore.score).ToString();
                                gdate5.Text = highscore.time;
                                break;
                        }
                    }
                }
                else
                {

                }
            }
            catch (Exception exception)
            {

            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow mw = new MenuWindow(this.client);
            this.Close();
            mw.Show();
        }
    }
}
