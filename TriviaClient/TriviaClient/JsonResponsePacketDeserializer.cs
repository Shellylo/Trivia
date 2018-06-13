using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient
{
    class JsonResponsePacketDeserializer
    {
        enum respCodes : uint
        {
            LOGIN_RESP_CODE = 1,
            SIGNUP_RESP_CODE,
            LOGOUT_RESP_CODE,
            GETROOMS_RESP_CODE,
            GETPLAYERSROOM_RESP_CODE,
            JOINROOM_RESP_CODE,
            CREATEROOM_RESP_CODE,
            GETHIGHSCORES_RESP_CODE,
            CLOSEROOM_RESP_CODE,
            STARTGAME_RESP_CODE,
            GETROOMSTATE_RESP_CODE,
            LEAVEROOM_RESP_CODE,
            JOINGAME_RESP_CODE,
            GETQUESTION_RESP_CODE,
            SUBMITANSWER_RESP_CODE,
            GETGAMERESULTS_RESP_CODE,
            LEAVEGAME_RESP_CODE
        };

        public struct LoginResponse
        {
            public uint status;

            public LoginResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct SignupResponse
        {
            public uint status;

            public SignupResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct LogoutResponse
        {
            public uint status;

            public LogoutResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct GetRoomsResponse
        {
            public uint status;
            public List<RoomData> rooms;

            public GetRoomsResponse(uint status, List<RoomData> rooms)
            {
                this.status = status;
                this.rooms = rooms;
            }
        };

        public struct GetPlayersInRoomResponse
        {
            public uint status;
            public List<string> users;

            public GetPlayersInRoomResponse(uint status, List<string> users)
            {
                this.status = status;
                this.users = users;
            }
        };

        public struct JoinRoomResponse
        {
            public uint status;

            public JoinRoomResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct CreateRoomResponse
        {
            public uint status;

            public CreateRoomResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct HighscoreResponse
        {
            public uint status;
            public List<Highscore> highscores;

            public HighscoreResponse(uint status, List<Highscore> highscores)
            {
                this.status = status;
                this.highscores = highscores;
            }
        };

        public struct CloseRoomResponse
        {
            public uint status;

            public CloseRoomResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct StartGameResponse
        {
            public uint status;

            public StartGameResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct GetRoomStateResponse
        {
            public uint status;
            public uint roomStatus;
            public List<string> players;
            public uint questionCount;
            public uint answerTimeout;

            public GetRoomStateResponse(uint status, uint roomStatus, List<string> players, uint questionCount, uint answerTimeout)
            {
                this.status = status;
                this.roomStatus = roomStatus;
                this.players = players;
                this.questionCount = questionCount;
                this.answerTimeout = answerTimeout;
            }

        };

        public struct LeaveRoomResponse
        {
            public uint status;

            public LeaveRoomResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct JoinGameResponse
        {
            public uint status;

            public JoinGameResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct GetQuestionResponse
        {
            public uint status;
            public string question;
            public List<string> answers;

            public GetQuestionResponse(uint status, string question, List<string> answers)
            {
                this.status = status;
                this.question = question;
                this.answers = answers;
            }
        };

        public struct SubmitAnswerResponse
        {
            public uint status;
            public string correctAnswer;
            public bool hasFinished;

            public SubmitAnswerResponse(uint status, string correctAnswer, bool hasFinished)
            {
                this.status = status;
                this.correctAnswer = correctAnswer;
                this.hasFinished = hasFinished;
            }
        };

        public struct GetGameResultsResponse
        {
            public uint status;
            public List<PlayerResults> results;

            public GetGameResultsResponse(uint status, List<PlayerResults> results)
            {
                this.status = status;
                this.results = results;
            }
        };

        public struct LeaveGameResponse
        {
            public uint status;

            public LeaveGameResponse(uint status)
            {
                this.status = status;
            }
        };

        public struct Highscore
        {
            public string username;
            public int score;
            public string time;

            public Highscore(string username, int score, string time)
            {
                this.username = username;
                this.score = score;
                this.time = time;
            }
        };

        public struct RoomData
        {
            public uint id;
            public string name;
            public uint maxPlayers; //was string changed to int
            public uint questionCount; //added this
            public uint timePerQuestion;
            public uint roomState; // 1 - waiting, 2 - closed, 3 - game started

            public RoomData(uint id, string name, uint maxPlayers, uint questionCount, uint timePerQuestion, uint roomState)
            {
                this.id = id;
                this.name = name;
                this.maxPlayers = maxPlayers;
                this.questionCount = questionCount;
                this.timePerQuestion = timePerQuestion;
                this.roomState = roomState;
            }
        };

        public struct PlayerResults
        {
            public string username;
            public uint correctAnswerCount;
            public uint wrongAnswerCount;
            public uint averageAnswerTime;

            public PlayerResults(string username, uint correctAnswerCount, uint wrongAnswerCount, uint averageAnswerTime)
            {
                this.username = username;
                this.correctAnswerCount = correctAnswerCount;
                this.wrongAnswerCount = wrongAnswerCount;
                this.averageAnswerTime = averageAnswerTime;
            }
        };

        public static T createStruct<T>(byte[] buff)
        {
            return JsonConvert.DeserializeObject<T>(new ASCIIEncoding().GetString(buff));
        }
    }
}
