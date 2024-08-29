#include "shell.h"

/**
 * print_alias - Display aliases; add, remove, or show based on input
 * @data: Program's data structure
 * @alias: Name of the alias to show, or NULL to show all
 * Return: 0 on success; non-zero on error
 */
int print_alias(data_of_program *data, char *alias)
{
	int index, length_of_alias;
	char output_buffer[250] = {'\0'};

	if (data->alias_list != NULL)
	{
		length_of_alias = str_length(alias);
		for (index = 0; data->alias_list[index]; index++)
		{
			if (alias == NULL ||
			    (str_compare(data->alias_list[index], alias, length_of_alias) &&
			     data->alias_list[index][length_of_alias] == '='))
			{
				int char_index;

				for (char_index = 0; data->alias_list[index][char_index]; char_index++)
				{
					output_buffer[char_index] = data->alias_list[index][char_index];
					if (data->alias_list[index][char_index] == '=')
						break;
				}
				output_buffer[char_index + 1] = '\0';
				buffer_add(output_buffer, "'");
				buffer_add(output_buffer, data->alias_list[index] + char_index + 1);
				buffer_add(output_buffer, "'\n");
				_print(output_buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - Fetch the value of a given alias
 * @data: Program's data structure
 * @name: Alias name to retrieve
 * Return: Value of the alias or NULL if not found
 */
char *get_alias(data_of_program *data, char *name)
{
	int index, name_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	name_length = str_length(name);

	for (index = 0; data->alias_list[index]; index++)
	{
		if (str_compare(name, data->alias_list[index], name_length) &&
		    data->alias_list[index][name_length] == '=')
		{
			return (data->alias_list[index] + name_length + 1);
		}
	}

	return (NULL);
}

/**
 * set_alias - Add or update an alias
 * @alias_string: Alias in the format name='value'
 * @data: Program's data structure
 * Return: 0 on success; non-zero on error
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int index, split_pos;
	char name_buffer[250] = {'\0'}, *resolved_alias = NULL;

	if (alias_string == NULL || data->alias_list == NULL)
		return (1);

	for (split_pos = 0; alias_string[split_pos]; split_pos++)
	{
		if (alias_string[split_pos] == '=')
		{
			resolved_alias = get_alias(data, alias_string + split_pos + 1);
			break;
		}
		name_buffer[split_pos] = alias_string[split_pos];
	}

	for (index = 0; data->alias_list[index]; index++)
	{
		if (str_compare(name_buffer, data->alias_list[index], split_pos) &&
		    data->alias_list[index][split_pos] == '=')
		{
			free(data->alias_list[index]);
			break;
		}
	}

	if (resolved_alias)
	{
		buffer_add(name_buffer, "=");
		buffer_add(name_buffer, resolved_alias);
		data->alias_list[index] = str_duplicate(name_buffer);
	}
	else
	{
		data->alias_list[index] = str_duplicate(alias_string);
	}

	return (0);
