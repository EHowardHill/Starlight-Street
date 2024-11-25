# Python script to fix index values in src/goodies.cpp

def fix_char_properties():
    input_file = 'src/goodies.cpp'
    output_file = 'src/goodies2.cpp'

    with open(input_file, 'r') as f:
        lines = f.readlines()

    state = 'outside_function'
    index = 0
    in_default_case = False
    modified_lines = []

    for line in lines:
        stripped_line = line.strip()

        if state == 'outside_function':
            if 'constexpr CharProperties create_char_properties(char ch)' in stripped_line:
                state = 'in_function'
            modified_lines.append(line)
        elif state == 'in_function':
            if 'switch (ch)' in stripped_line:
                state = 'in_switch'
            modified_lines.append(line)
        elif state == 'in_switch':
            if stripped_line.startswith('case '):
                in_default_case = False
                modified_lines.append(line)
            elif stripped_line.startswith('default:'):
                in_default_case = True
                modified_lines.append(line)
            elif 'return {' in stripped_line:
                if in_default_case:
                    modified_lines.append(line)
                else:
                    # Process the return line
                    start_idx = stripped_line.find('{')
                    end_idx = stripped_line.find('}')
                    return_content = stripped_line[start_idx+1:end_idx]
                    return_values = [v.strip() for v in return_content.split(',')]
                    # Modify the first value to be index
                    return_values[0] = str(index)
                    index += 1
                    # Construct the new return line
                    indent = line[:line.find('return')]
                    new_return_line = indent + 'return {' + ', '.join(return_values) + '};\n'
                    modified_lines.append(new_return_line)
            elif stripped_line == '}':
                # End of switch statement
                state = 'after_switch'
                modified_lines.append(line)
            else:
                modified_lines.append(line)
        elif state == 'after_switch':
            if stripped_line == '}':
                # End of function
                state = 'outside_function'
            modified_lines.append(line)
        else:
            # Should not reach here
            modified_lines.append(line)

    # Write the modified lines back to the file
    with open(output_file, 'w') as f:
        f.writelines(modified_lines)

# Run the function to fix the C++ code
fix_char_properties()
