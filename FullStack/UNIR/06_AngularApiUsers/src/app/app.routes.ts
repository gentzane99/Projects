import { Routes } from '@angular/router';
import { HomeComponent } from './pages/home/home.component';
import { UserComponent } from './pages/user/user.component';
import { UserFormComponent } from './pages/user-form/user-form.component';

export const routes: Routes = [
    {path:"", pathMatch: 'full', redirectTo: 'home'},
    {path:"home", component: HomeComponent},
    {path:"user/:idUser", component: UserComponent},
    {path: "newuser", component: UserFormComponent},
    {path: "updateuser/:idUser", component: UserFormComponent},
    {path: "**", redirectTo:'home'}
];
