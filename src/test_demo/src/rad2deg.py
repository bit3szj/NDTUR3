import math

while True:
    # 询问用户输入弧度值
    radian_input = input("请输入弧度值 (输入 'exit' 退出程序): ")
    
    if radian_input.lower() == 'exit':
        print("程序已退出。")
        break
    
    try:
        # 将输入的字符串转换为浮点数
        radian_value = float(radian_input)
        
        # 转换为角度值
        degree_value = math.degrees(radian_value)
        
        # 输出结果
        print(f"{radian_value} 弧度等于 {degree_value} 度。")
    except ValueError:
        # 如果转换失败，提示用户输入不合法
        print("输入不合法，请输入一个有效的数字。")