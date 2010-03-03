#ifndef DBMS_COLUMN_TYPES_ICOLUMNTYPE_H
#define DBMS_COLUMN_TYPES_ICOLUMNTYPE_H

#include <ostream>

#include <DB/Core/Field.h>
#include <DB/Core/Column.h>


namespace DB
{


/** Метаданные типа для хранения (столбца).
  * Содержит методы для сериализации/десериализации.
  */
class IColumnType
{
public:
	/// Основное имя типа (например, BIGINT UNSIGNED).
	virtual std::string getName() const = 0;

	/** Предполагается, что проверка статуса stream-ов производится вызывающей стороной.
	  */

	/** Бинарная сериализация - для сохранения на диск / в сеть и т. п.
	  * Обратите внимание, что присутствует по два вида методов
	  * - для работы с единичными значениями и целыми столбцами.
	  */
	virtual void serializeBinary(const Field & field, std::ostream & ostr) const = 0;
	virtual void deserializeBinary(Field & field, std::istream & istr) const = 0;
	virtual void serializeBinary(const Column & column, std::ostream & ostr) const = 0;
	/** Считать не более limit значений. */
	virtual void deserializeBinary(Column & column, std::istream & istr, size_t limit) const = 0;

	/** Текстовая сериализация - для вывода на экран / сохранения в текстовый файл и т. п.
	  * Без эскейпинга и квотирования.
	  */
	virtual void serializeText(const Field & field, std::ostream & ostr) const = 0;
	virtual void deserializeText(Field & field, std::istream & istr) const = 0;

	/** Текстовая сериализация с эскейпингом, но без квотирования.
	  * Есть реализация по умолчанию, которая подходит почти для всех случаев.
	  */
	virtual void serializeTextEscaped(const Field & field, std::ostream & ostr) const = 0;
	virtual void deserializeTextEscaped(Field & field, std::istream & istr) const = 0;

	/** Текстовая сериализация в виде литерала, который может быть вставлен в запрос.
	  * Если compatible = true, то значение типа "массив" и "кортеж" ещё дополнительно записывается в кавычки,
	  *  чтобы текстовый дамп можно было загрузить в другую СУБД с этими значениями в виде строки.
	  */
	virtual void serializeTextQuoted(const Field & field, std::ostream & ostr, bool compatible = false) const = 0;
	virtual void deserializeTextQuoted(Field & field, std::istream & istr, bool compatible = false) const = 0;


	virtual ~IColumnType() {}
};

}

#endif
