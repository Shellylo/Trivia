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
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for ResultsWindow.xaml
    /// </summary>
    public partial class ResultsWindow : Window
    {
        private Client client;
        private DispatcherTimer dt;
        private bool isForcedClosing;

        public ResultsWindow(Client client)
        {
            InitializeComponent();
            this.client = new Client(client);
            this.isForcedClosing = true;
            this.dt = new DispatcherTimer();
            this.dt.Tick += updateScores;
            this.dt.Interval = new TimeSpan(0, 0, 1);
            this.dt.Start();
        }

        private void updateScores(Object sender, EventArgs e)
        {
            try
            {
                JsonResponsePacketDeserializer.GetGameResultsResponse gameResultsResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.GetGameResultsResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.GETGAMERESULTS_REQ_CODE);
                if (gameResultsResp.status == 1)
                {
                    this.Scores.Children.Clear();
                    while (gameResultsResp.results.Count != 0)
                    {
                        int maxIndex = findMaxScore(gameResultsResp.results);
                        Grid gr = new Grid();
                        gr.ColumnDefinitions.Add(new ColumnDefinition());
                        gr.ColumnDefinitions.Add(new ColumnDefinition());
                        TextBlock player = new TextBlock();
                        player.Text = gameResultsResp.results[maxIndex].username;
                        player.FontSize = 20;
                        Grid.SetColumn(player, 0);
                        player.HorizontalAlignment = HorizontalAlignment.Left;
                        player.VerticalAlignment = VerticalAlignment.Center;
                        gr.Children.Add(player);
                        TextBlock score = new TextBlock();
                        score.Text = (gameResultsResp.results[maxIndex].correctAnswerCount).ToString();
                        score.FontSize = 20;
                        Grid.SetColumn(score, 1);
                        score.HorizontalAlignment = HorizontalAlignment.Right;
                        score.VerticalAlignment = VerticalAlignment.Center;
                        gr.Children.Add(score);
                        this.Scores.Children.Add(gr);
                        gameResultsResp.results.RemoveAt(maxIndex);
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

        private int findMaxScore(List<JsonResponsePacketDeserializer.PlayerResults> scores)
        {
            int index = 0;
            for (int i = 1; i < scores.Count; i++)
            {
                if (scores[i].correctAnswerCount > scores[index].correctAnswerCount)
                {
                    index = i;
                }
            }
            return index;
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                JsonResponsePacketDeserializer.LeaveGameResponse leaveGameResp = this.client.SendAndReceive<JsonResponsePacketDeserializer.LeaveGameResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LEAVEGAME_REQ_CODE);
                if (leaveGameResp.status == 1)
                {
                    this.isForcedClosing = false;
                    this.dt.Stop();
                    MenuWindow mw = new MenuWindow(this.client);
                    this.Close();
                    mw.Show();
                }
                else
                {

                }
            }
            catch (Exception exception)
            {

            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (this.isForcedClosing)
            {
                this.client.SendAndReceive<JsonResponsePacketDeserializer.LogoutResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LEAVEGAME_REQ_CODE);
                this.client.SendAndReceive<JsonResponsePacketDeserializer.LogoutResponse>(null, (uint)JsonRequestPacketSerializer.reqCodes.LOGOUT_REQ_CODE);
            }
        }
    }
}
