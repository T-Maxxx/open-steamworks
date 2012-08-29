/*
	This file is a part of "Chat Logger++"
	�2k12, Didrole
	
	License : Public domain
*/

#pragma once

#include <map>
#include <wx/thread.h>
#include <wx/ffile.h>
#include "Steamworks.h"

class CLogger : public wxThread
{
public:
	CLogger();
	~CLogger();

	void SetLogDirectory(const wxString& path);
	void SetFilenameFormat(const wxString& format);
	void SetReplacementChar(const wxString& string);
	void SetMessageFormat(const wxString& format);
	void SetEmoteFormat(const wxString& format);
	void SetSeparationString(const wxString& string);
	void SetDateFormat(const wxString& format);
	void SetTimeFormat(const wxString& format);

	void UseClientInterfaces(bool bUse = false);

	static wxString TagsReplace(const wxString& string, const wxArrayString& tags, const wxArrayString& replacements);

private:
	bool InitSteam();
	void CleanupSteam();
	void CallbackHandlerThread();

	void OnIPCFailure(IPCFailure_t* pIPCFailure);
	void OnFriendChatMsg(FriendChatMsg_t* pFriendChatMsg);
	void OnChatRoomMsg(ChatRoomMsg_t* pChatRoomMsg);
	void OnChatRoomDlgClose(ChatRoomDlgClose_t* pChatRoomDlgClose);

	wxFFile* GetLogFile(CSteamID steamID, bool bOpenIfNeeded = true);
	void CloseLogs();

	virtual ExitCode Entry();

	void FormatFilename(wxString& string, CSteamID steamID);
	void FormatMessage(wxString& string, CSteamID steamID, const char* cszMessage);

	bool m_bUseClientInterfaces;

	CSteamAPILoader m_steamLoader;
	HSteamPipe m_hPipe;
	HSteamUser m_hUser;
	ISteamClient012* m_pSteamClient;
	ISteamUser016* m_pSteamUser;
	ISteamFriends013* m_pSteamFriends;
	IClientFriends* m_pClientFriends;

	std::map<CSteamID, wxFFile*> m_logsOpened;

	wxString m_logDirectory;
	wxString m_filenameFormat;
	wxString m_replacementChar;
	wxString m_messageFormat;
	wxString m_emoteFormat;
	wxString m_separationString;
	wxString m_dateFormat;
	wxString m_timeFormat;
	
	wxMutex m_configLock;
	wxMutex m_steamLock;
};