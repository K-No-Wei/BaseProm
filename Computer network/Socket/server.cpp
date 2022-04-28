#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

/*��ʼ���׽��ֿ�*/
void initialization() {
	WORD w_req = MAKEWORD(2,2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req,&wsadata);
	if (err != 0) {
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	}
	else {
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "�׽��ֿ�汾�Ų�����" << endl;
	}
	else {
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	}
}

int main() {
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[100];
	char recv_buf[100];
	//���������׽��֣����������׽���
	SOCKET s_server;
	SOCKET s_accept;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(12341);
	//�����׽���
	s_server = socket(AF_INET,SOCK_STREAM,0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "�׽��ְ�ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else {
		cout << "�׽��ְ󶨳ɹ���" << endl;
	}
	//�����׽���Ϊ����״̬
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "���ü���ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else {
		cout << "���ü����ɹ���" << endl;
	}
	cout << "��������ڼ������ӣ����Ե�---" << endl;
	//������������
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "����ʧ�ܣ�" << endl;
		WSACleanup();
		return 0;
	}
	cout << "���ӽ�����׼����������" << endl;
	//��������
	while (1) {
		recv_len = recv(s_accept,recv_buf,100,0);
		if (recv_len < 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		else {
			cout << "�ͻ�����Ϣ��" << recv_buf << endl;
		}
		cout << "������ظ���Ϣ��";
		cin >> send_buf;
		send_len = send(s_accept,send_buf,100,0);
		if (send_len < 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
	}
	return 0;
}
