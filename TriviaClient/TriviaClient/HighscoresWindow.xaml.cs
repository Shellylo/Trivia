﻿using System;
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
        private bool isForcedClosing;

        public HighscoresWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
            this.isForcedClosing = true;
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
                                this.username1.Text = highscore.username;
                                this.gscore1.Text = (highscore.score).ToString();
                                this.gdate1.Text = highscore.time;
                                break;
                            case 1:
                                this.username2.Text = highscore.username;
                                this.gscore2.Text = (highscore.score).ToString();
                                this.gdate2.Text = highscore.time;
                                break;
                            case 2:
                                this.username3.Text = highscore.username;
                                this.gscore3.Text = (highscore.score).ToString();
                                this.gdate3.Text = highscore.time;
                                break;
                            case 3:
                                this.username4.Text = highscore.username;
                                this.gscore4.Text = (highscore.score).ToString();
                                this.gdate4.Text = highscore.time;
                                break;
                            case 4:
                                this.username5.Text = highscore.username;
                                this.gscore5.Text = (highscore.score).ToString();
                                this.gdate5.Text = highscore.time;
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
            this.isForcedClosing = false;
            MenuWindow mw = new MenuWindow(this.client);
            this.Close();
            mw.Show();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(this.isForcedClosing)
            {
                this.client.SendAndReceive<JsonResponsePacketDeserializer.LogoutResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LOGOUT_REQ_CODE);
            }
        }
    }
}
