# ThoughtWorks 2018У԰��Ƹ��ҵ

ʵ����ë�򳡵�ԤԼ����ϵͳ, ��Ŀ��C++ʵ��, �����¼���Ŀ¼:

### include:
������Ŀ��ͷ�ļ��������¼���:
booking_item.h: ��ʾԤԼϵͳ��һ��ԤԼ��¼, ��������, ʱ���, uid, ��ʼʱ�������, ����ʱ�������
booking_management.h: ԤԼϵͳ�����ݽӿ�, ��Ҫ���ṩԤԼ, ȡ��ԤԼ,����ʾ��������������Ĺ���, �ڲ��ṩ�˼�����������ʱ��εļ۸�
date_util.h: �������ڵĹ�����, ����������ڵĺϷ���, ʱ��εĺϷ���, ����ʱ���ת��Ϊ����������ת��Ϊ�����ַ���
mlog.h: �Լ�ʵ�ֵļ��װ��log����
string_util.h: �ַ����Ĵ�������, ����trim, split����

### src:
������Ŀ��ʵ�ִ��룬�����¼���:
main.cpp: ��������
booking_management.cpp: ��Ӧ��booking_management.h��ʵ�ִ���
date_util.cpp: ��Ӧ��date_util.h��ʵ�ִ���
mlog.cpp: ��Ӧ��mlog.h��ʵ�ִ���
string_util.cpp: ��Ӧ��string_util.h��ʵ�ִ���

### log:
��Ŀ����־·��, ���������������Զ������ĸ���־�ļ�, ����debug.log, trace.log, warning.log, fatal.log

### out:
��Ŀ��������ɵĿ�ִ���ļ�·��, ��Ҫ��Դ�ļ����ɵ�һϵ��Ŀ���ļ���main��ִ���ļ�


Makefile�ļ�, ��ϸ˵������Ŀ�ı������, ������Ҫ��֧��C++14��׼, �Ƽ�ʹ��clang++
����: make
����: ./out/main


