using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    class JsonRequestPacketDeserializer
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
        };

        public struct SignupResponse
        {
            public uint status;
        };

        public struct LogoutResponse
        {
            public uint status;
        };

        public struct GetRoomsResponse
        {
            public uint status;
            public std::vector<RoomData> rooms;
        };

        public struct GetPlayersInRoomResponse
        {
            public uint status;
            public std::vector<string> users;
        };

        public struct JoinRoomResponse
        {
            public uint status;
        };

        public struct CreateRoomResponse
        {
            public uint status;
        };

        public struct HighscoreResponse
        {
            public uint status;
            public std::vector<Highscore> highscores;
        };

        public struct CloseRoomResponse
        {
            public uint status;
        };

        public struct StartGameResponse
        {
            public uint status;
        };

        public struct GetRoomStateResponse
        {
            public uint status;
            public uint roomStatus;
            public std::vector<string> players;
            public uint questionCount;
            public uint answerTimeout;
        };

        public struct LeaveRoomResponse
        {
            public uint status;
        };

        public struct JoinGameResponse
        {
            public uint status;
        };

        public struct GetQuestionResponse
        {
            public uint status;
            public string question;
            public std::vector<string> answers;
        };

        public struct SubmitAnswerResponse
        {
            public uint status;
            public string correctAnswer;
            public bool hasFinished;
        };

        public struct GetGameResultsResponse
        {
            public uint status;
            public std::vector<PlayerResults> results;
        };

        public struct LeaveGameResponse
        {
            uint status;
        };

        public struct PlayerResults
        {
            string username;
            uint correctAnswerCount;
            uint wrongAnswerCount;
            uint averageAnswerTime;
        };
    }
}
