import mido
import numpy as np
# 解析文件，提取其中的note on/off 和 note 和time ,以该格式输出: [[note on/off1, note1, time1],[note on/off2, note2, time2],...]

def replace_text_at_line(new_text, destination_file, line_number):
    # 读取目标文件内容
    with open(destination_file, "r") as f:
        destination_content = f.readlines()

    # 替换指定行的文本
    destination_content[line_number - 1] = new_text + '\n'

    # 将修改后的内容写回文件
    with open(destination_file, "w") as f:
        f.writelines(destination_content)


def parse_midi(file_name):

    mid = mido.MidiFile(file_name)  # 打开并加载MIDI文件
    # print(mid)
    notes = []  # 用于存储音符信息的列表
    
    for msg in mid:
    
        # 如果消息类型为'note_on'，则添加音符开启事件
        if msg.type == 'note_on':
            if msg.time!=0:
                notes.append([0, int(msg.time*700)])

        # 如果消息类型为'note_off'，则添加音符关闭事件
        elif msg.type == 'note_off' :
            notes.append([msg.note-43, int(msg.time*700)])
    return [item for sublist in notes for item in sublist]

if __name__ == '__main__':

    notes = parse_midi('untitled.mid')
    print(notes)
    file = open("main.c", "r")
    lines = file.readlines()
    file.close()

        # 输入要替换的行号和新内容数组
    line_number_to_replace = int(24)
    # 将整数列表转换为字符串列表
    notes = list(map(str, notes))
    comma_separated_string = ','.join(notes) + ',0xFF'
    # 指定源文件和目标文件以及要插入的行号
    destination_file = "main.c"
    line_number = 23
    # 调用函数来替换指定行的文本
    replace_text_at_line(comma_separated_string, destination_file, line_number)