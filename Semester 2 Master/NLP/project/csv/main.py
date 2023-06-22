# title (third field) and description (sixth field)
# category is fifth

category_filter = ['World', 'Sports', 'Business', 'Sci/Tech']

with open("newsSpace", errors='ignore') as f, open("news.csv", 'w', encoding='utf-8') as writer:
    writer.write("category;title;description\n")
    lines = f.readlines()
    print(len(lines))
    for i, line in enumerate(lines):
        if i % 100 == 0:
            print(i, len(lines))

        tokens = line.split('\t')
        if len(tokens) < 6:
            continue

        title = tokens[2].strip().replace(';', ' ')
        category = tokens[4].strip()
        description = tokens[5].strip().replace(';', ' ')

        if category not in category_filter:
            continue

        if len(description) == 0:
            continue
        if description[-1] == '\\':
            description = description[:-1]
        if len(description) == 0:
            continue
        if description[-1] == ',':
            description = description[:-1]


        writer.write(f'{category};{title};{description}\n')
