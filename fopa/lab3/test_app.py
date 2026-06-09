import unittest
import app as application


class TestChecklist(unittest.TestCase):

    def setUp(self):
        application.app.config['TESTING'] = True
        self.client = application.app.test_client()

        # Очищаем список задач и сбрасываем счётчик
        application.tasks.clear()
        application.next_id = 1

    # Тесты главной страницы

    def test_index_returns_200(self):
        response = self.client.get('/')
        self.assertEqual(response.status_code, 200)

    def test_index_shows_empty_message(self):
        response = self.client.get('/')
        self.assertIn('Список пуст'.encode('utf-8'), response.data)

    def test_index_shows_tasks(self):
        application.tasks.append({'id': 1, 'title': 'Тестовая задача', 'done': False})
        response = self.client.get('/')
        self.assertIn('Тестовая задача'.encode('utf-8'), response.data)

    # Тесты добавления задачи

    def test_add_task(self):
        self.client.post('/add', data={'title': 'Новая задача'})
        self.assertEqual(len(application.tasks), 1)
        self.assertEqual(application.tasks[0]['title'], 'Новая задача')

    def test_add_task_default_done_false(self):
        self.client.post('/add', data={'title': 'Задача'})
        self.assertFalse(application.tasks[0]['done'])

    def test_add_task_increments_id(self):
        self.client.post('/add', data={'title': 'Первая'})
        self.client.post('/add', data={'title': 'Вторая'})
        ids = [t['id'] for t in application.tasks]
        self.assertEqual(ids, [1, 2])

    def test_add_empty_task_ignored(self):
        self.client.post('/add', data={'title': ''})
        self.assertEqual(len(application.tasks), 0)

    def test_add_whitespace_task_ignored(self):
        self.client.post('/add', data={'title': '   '})
        self.assertEqual(len(application.tasks), 0)

    def test_add_redirects_to_index(self):
        response = self.client.post('/add', data={'title': 'Задача'})
        self.assertEqual(response.status_code, 302)
        self.assertIn('/', response.location)

    # Тесты переключения статуса

    def test_toggle_marks_done(self):
        application.tasks.append({'id': 1, 'title': 'Задача', 'done': False})
        self.client.post('/toggle/1')
        self.assertTrue(application.tasks[0]['done'])

    def test_toggle_marks_undone(self):
        application.tasks.append({'id': 1, 'title': 'Задача', 'done': True})
        self.client.post('/toggle/1')
        self.assertFalse(application.tasks[0]['done'])

    def test_toggle_only_affects_target_task(self):
        application.tasks.append({'id': 1, 'title': 'Первая', 'done': False})
        application.tasks.append({'id': 2, 'title': 'Вторая', 'done': False})
        self.client.post('/toggle/1')
        self.assertTrue(application.tasks[0]['done'])
        self.assertFalse(application.tasks[1]['done'])

    # Тесты редактирования

    def test_edit_task_title(self):
        application.tasks.append({'id': 1, 'title': 'Старое название', 'done': False})
        self.client.post('/edit/1', data={'title': 'Новое название'})
        self.assertEqual(application.tasks[0]['title'], 'Новое название')

    def test_edit_empty_title_ignored(self):
        application.tasks.append({'id': 1, 'title': 'Старое название', 'done': False})
        self.client.post('/edit/1', data={'title': ''})
        self.assertEqual(application.tasks[0]['title'], 'Старое название')

    def test_edit_does_not_change_done_status(self):
        application.tasks.append({'id': 1, 'title': 'Задача', 'done': True})
        self.client.post('/edit/1', data={'title': 'Новое'})
        self.assertTrue(application.tasks[0]['done'])

    # Тесты удаления

    def test_delete_task(self):
        application.tasks.append({'id': 1, 'title': 'Задача', 'done': False})
        self.client.post('/delete/1')
        self.assertEqual(len(application.tasks), 0)

    def test_delete_correct_task(self):
        application.tasks.append({'id': 1, 'title': 'Первая', 'done': False})
        application.tasks.append({'id': 2, 'title': 'Вторая', 'done': False})
        self.client.post('/delete/1')
        self.assertEqual(len(application.tasks), 1)
        self.assertEqual(application.tasks[0]['title'], 'Вторая')

    def test_delete_redirects_to_index(self):
        application.tasks.append({'id': 1, 'title': 'Задача', 'done': False})
        response = self.client.post('/delete/1')
        self.assertEqual(response.status_code, 302)


if __name__ == '__main__':
    unittest.main(verbosity=2)
